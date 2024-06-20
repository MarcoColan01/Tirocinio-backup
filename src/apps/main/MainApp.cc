#include "MainApp.h"

#include "apps/mec/DeviceApp/DeviceAppMessages/DeviceAppPacket_Types.h"
#include "apps/mec/DeviceApp/DeviceAppMessages/DeviceAppPacket_m.h"
#include "CellularHandler.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "modules/controlLaw/CACCControlLaw.h"
#include "modules/controlLaw/PLOEGControlLaw.h"
#include "modules/powercontroller/PowerController.h"


#define RAT_EVALUATION_MSG_NAME "ratEvaluation"


Define_Module(MainApp);

void MainApp::initialize(int stage) {

    if (stage == inet::INITSTAGE_LOCAL){
        lowLevelController = check_and_cast<LowLevelController *>(getParentModule()->getSubmodule("controller"));
        decider = check_and_cast<BaseDecider*>(getParentModule()->getSubmodule("decider"));
        instructionMng = new InstructionManager(decider, this);

        statusUpdateInterval = par("statusUpdateInterval").doubleValue();
        selfUpdateMsg = new cMessage("selfUpdate");

    }

    if (stage == inet::INITSTAGE_APPLICATION_LAYER) {
        // Inizializzazione socket v2v
        UdpSocket *v2vSocket = new UdpSocket();
        L3Address destAddress;
        L3AddressResolver().tryResolve(par("mcastAddress"), destAddress);
        v2vSocket->setOutputGate(gate("socketOut"));
        const char *interface = par("v2vInterface");
        IInterfaceTable *ift =
                getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        NetworkInterface *ie = ift->findInterfaceByName(interface);
        v2vSocket->bind(ie->getIpv4Address(), 9001); // TODO: from parameter
        v2vSocket->setMulticastOutputInterface(ie->getInterfaceId());
        MulticastGroupList mgl = ift->collectMulticastGroups();
        v2vSocket->joinLocalMulticastGroups(mgl);
        socketsMap[V2V_SOCKET] = new SocketWrapper(v2vSocket, destAddress, 9001);

        // Inizializzazione socket con deviceApp
        UdpSocket *deviceAppSocket = new UdpSocket();
        deviceAppSocket->setOutputGate(gate("socketOut"));
        deviceAppSocket->bind(4001);  // TODO: passare tramite parametro

        socketsMap[DAPP_SOCKET] = new SocketWrapper(deviceAppSocket, L3Address("127.0.0.1"), par("deviceAppPort"));
        socketsMap[DAPP_SOCKET]->setCallback(this);
    }

    if (stage == inet::INITSTAGE_LAST){
        scheduleAfter(par("startTime").doubleValue() + statusUpdateInterval, new cMessage("selfStart"));  // importante il delay per simu5g
        scheduleAfter(statusUpdateInterval + uniform(SimTime(-50, SIMTIME_US), SimTime(50, SIMTIME_US)), selfUpdateMsg);
    }

}



void MainApp::handleStatusUpdate(cMessage *msg){
    auto carStatus = lowLevelController->getStatus();
    if (firstStatus){
        vehiclePlatoonLogicRegistration(carStatus);
        firstStatus = false;
    }

    for (const auto& el : activeHandlers)
        el.second->onNewDataArrived(carStatus);


    // IMPORTANT Add random time between 1 us and 100 us to break potential time alignment among vehicle
    scheduleAfter(statusUpdateInterval + uniform(SimTime(-50, SIMTIME_US), SimTime(50, SIMTIME_US)), msg);

    if (activeHandlers.size()>0){
        //schedule all RATs check after few microseconds to allow registration of onboard sensor data avoiding nan
        scheduleAfter(SimTime(10, SIMTIME_US), new cMessage(RAT_EVALUATION_MSG_NAME));
    }
}


void MainApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        //Inizializzazione MEC application
        if (strcmp(msg->getName(), "selfStart") == 0){
            startMECApp();
            delete msg;
        } else if (msg == selfUpdateMsg){ // A single update message triggers all the handlers
            handleStatusUpdate(msg);

        } else if(strcmp(msg->getName(), RAT_EVALUATION_MSG_NAME ) == 0){
            decider->evaluateAllRatReliability();
            delete msg;
        }
        //Se non è un selfmessage allora è un pacchetto di rete
    } else {
        //Vado a controllare a quale socket appartiene e ci chiamo processMessage()
        //NB: Sono gli handler a settare i callback sulle socket,
        // tranne sulla socket in localhost con DeviceApp. In quel caso la callback è settata
        // in questa classe
        //Quindi alla chiamata di processMessage seguirà la chiamata del callback
        //socketDataArrived
        auto it = socketsMap.begin();
        for (; it != socketsMap.end() && !it->second->socket->belongsToSocket(msg);
                it++)
            ;
        ASSERT(it != socketsMap.end());
        it->second->socket->processMessage(msg);
    }
}







void MainApp::startMECApp() {
    Packet *packet = new Packet("MecAppStart");
    auto start = inet::makeShared<DeviceAppStartPacket>();
    start->setType(START_MECAPP);
    string mecAppName = par("mecAppName").stdstringValue();
    start->setMecAppName(mecAppName.c_str());
    start->setChunkLength(inet::B(2 + mecAppName.size() + 1));
    start->addTagIfAbsent<inet::CreationTimeTag>()->setCreationTime(simTime());
    packet->insertAtBack(start);
    socketsMap.find(DAPP_SOCKET)->second->send(packet);
}





//Dati arrivati da DeviceApp
void MainApp::socketDataArrived(UdpSocket *socket, Packet *packet) {
    auto mePkt = packet->peekAtFront<DeviceAppPacket>();
    if (strcmp(mePkt->getType(), ACK_START_MECAPP) != 0)
        throw new cRuntimeError("MainApp::socketDataArrived - \tFATAL! Unrecognized packet");

    auto pkt = packet->peekAtFront<DeviceAppStartAckPacket>();
    if (pkt->getResult()) {
        // Inizializzazione socket MEC
        L3Address address = L3AddressResolver().resolve(pkt->getIpAddress());
        int port = pkt->getPort();
        EV_INFO << "MainApp::socketDataArrived: received Mec info [IP: " << address.str()
                                                                               << "; PORT: " << port << "]" << endl;
        UdpSocket *mecSocket = new UdpSocket();
        mecSocket->setOutputGate(gate("socketOut"));
        mecSocket->bind(4002);
        socketsMap[MEC_SOCKET] = new SocketWrapper(mecSocket, address, port);

        Handler *cellularHandler = new CellularHandler(this);
        cellularHandler->setOnNewVehiclePacketListener(this);
        cellularHandler->init(socketsMap);
        activeHandlers[cellularHandler->getName()] = cellularHandler;
        EV << "ORA PARTE ONLINE " << endl;
    }
    delete packet;
}


//Istruzione ricevuta da un handler
void MainApp::onNewInstructionReceived(Handler *handler, const vehicle_instruction_t instruction){
    if (firstInstruction) {
        //Solo la prima volta si setta la speedMode in base al veicolo
        //Il leader guida in modo sicuro, tenenedo una distanza di sicurezza
        //da qualsiasi cosa si trova davanti
        lowLevelController->setSafeSpeed(instruction.isLeader);
        firstInstruction = false;
    }

    //Se non è un leader, esegui l'istruzione. In teoria in leader NON
    //dovrebbe mai ricevere istruzioni
    if (!instruction.isLeader) {
        handler->updateInstructionManager(instructionMng, instruction.accelaration);
        instruction_t bestInstruction = instructionMng->getBestInstruction();
        std::cout << "best instruction: " << bestInstruction.instruction << std::endl;
        std::cout << "car id: " << this->getParentModule()->getFullName() << std::endl;


        lowLevelController->setAcceleration(bestInstruction.instruction);
    }
}



//Istruzione ricevuta da un handler
void MainApp::onNewInstructionReceived(Handler *handler, const VehicleInstructionPacket *instruction) {
    vehicle_instruction_t instruction_t = {instruction->isLeader(), instruction->getAcceleration()};
    onNewInstructionReceived(handler, instruction_t);
}





//Quando ricevo le informazioni del platoon (Handler V2N), faccio
//partire anche l'handler V2V
void MainApp::onPlatoonInfoReceived(
        Handler *handler, const VehiclePlatoonInfoPacket *platoonInfo) {
    EV_INFO << "MainApp::onPlatoonInfoReceived: unique id:" << platoonInfo->getPlatoonId() <<"-"<< platoonInfo->getPlatoonCarId() << endl;
    platoonCarId = platoonInfo->getPlatoonCarId();
    platoonId = platoonInfo->getPlatoonId();
    PLOEGControlLaw *ploegControlLaw = check_and_cast<PLOEGControlLaw *>(
    //CACCControlLaw *caccControlLaw = check_and_cast<CACCControlLaw *>(
            getParentModule()->getSubmodule("controlLaw"));

    PowerController *powerController = nullptr;

    if (getParentModule()->par("hasDsrcPowerControl").boolValue()){
        throw new cRuntimeError("Do not use PowerController, it is not implemented anymore!");
    }

    //DsrcHandler *dsrcHandler = new DsrcHandler(platoonId, platoonCarId, this, caccControlLaw, powerController, getOnboardControlLawMode());

    DsrcHandler *dsrcHandler = new DsrcHandler(platoonId, platoonCarId, this, ploegControlLaw, powerController, getOnboardControlLawMode());
    dsrcHandler->setOnNewVehiclePacketListener(this);
    dsrcHandler->init(socketsMap);
    activeHandlers[dsrcHandler->getName()] = dsrcHandler;

}



OnboardControlLawMode MainApp::getOnboardControlLawMode(){
    if (par("onboardControlLawMode").stdstringValue().compare("synchronous") == 0){
        return OnboardControlLawMode::SYNCHRONOUS;
    }
    if (par("onboardControlLawMode").stdstringValue().compare("asynchronous") == 0){
        return OnboardControlLawMode::ASYNCHRONOUS;
    }
    // This should never happen
    throw new cRuntimeError("Unknown OnBoardControlLawMode");
}


void MainApp::vehiclePlatoonLogicRegistration(status_t status){
    GlobalPlatoonsManager *gpm = check_and_cast<GlobalPlatoonsManager *>(getModuleByPath("<root>.globalPlatoonsManager"));
    bool registrationOk =  gpm->vehiclePlatoonLogicRegistration(status);
    if (!registrationOk)
        throw new cRuntimeError("Something wrong in registering the vehicle");

}
