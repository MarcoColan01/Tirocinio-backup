#include "VirtualVehicleMECApp.h"

#include "apps/mec/DeviceApp/DeviceAppMessages/DeviceAppPacket_Types.h"

#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet_m.h"

#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"

#include "nodes/mec/utils/httpUtils/httpUtils.h"
#include "nodes/mec/utils/httpUtils/json.hpp"
#include "nodes/mec/MECPlatform/MECServices/packets/HttpResponseMessage/HttpResponseMessage.h"

#include "apps/packets/VehicleControlPacket_m.h"
#include "apps/packets/VehicleControlPacket_Types.h"

#include "apps/packets/PlatoonInfo_Types.h"

#include <fstream>
#include <string>

Define_Module(VirtualVehicleMECApp);

using namespace inet;
using namespace omnetpp;
using namespace std;

VirtualVehicleMECApp::VirtualVehicleMECApp() : MecAppBase() {
}
VirtualVehicleMECApp::~VirtualVehicleMECApp() {
    delete sendStartAckPacket_;
}

void VirtualVehicleMECApp::initialize(int stage) {
    MecAppBase::initialize(stage);

    if (stage == inet::INITSTAGE_APPLICATION_LAYER){

        ueSocket.setOutputGate(gate("socketOut"));
        localUePort = par("localUePort");
        ueSocket.bind(localUePort);
        //ueSocket.setCallback(this);

        mp1Socket_ = addNewSocket();

        // connect with the service registry
        cMessage *msg = new cMessage("connectMp1");
        scheduleAt(simTime() + 0, msg);

        sendStartAckPacket_ = new cMessage("sendStartAckPacket");
        startAckTimeout_ = par("startAckTimeout");

        minStatusDistance = par("minStatusDistance");
        lastStatusReceived = simTime();

        packetDropRate_ = par("packetDropRate");

        statusAgeOfInfoSignal = registerSignal("statusAgeOfInfoSignal");
        statusDiscardedSignal = registerSignal("statusDiscardedSignal");
        vehicleStatusPacketDelay = registerSignal("vehicleStatusPacketDelay");
    }

    if (stage == inet::INITSTAGE_LAST){
        connect(mp1Socket_, mp1Address, mp1Port);
    }
}


void VirtualVehicleMECApp::handleProcessedMessage(cMessage *msg)
{
    if (!msg->isSelfMessage()) {
        if(ueSocket.belongsToSocket(msg))
        {
            handleUeMessage(msg);
            delete msg;
            return;
        }
    }
    MecAppBase::handleProcessedMessage(msg);
}


void VirtualVehicleMECApp::finish() {

}

void VirtualVehicleMECApp::handleSelfMessage(cMessage *msg) {
    if (strcmp(msg->getName(), "sendStartAckPacket") == 0) {
        sendStartAckPacket();
    }
}


void VirtualVehicleMECApp::established(int connId) {
    if (connId == mp1Socket_->getSocketId()) {
        EV << "VirtualVehicleMECApp::established - Mp1Socket" << endl;
        // get endPoint of the required service
        const char *uri =
                "/example/mec_service_mgmt/v1/services?ser_name=PlatoonService";
        std::string host = mp1Socket_->getRemoteAddress().str() + ":"
                + std::to_string(mp1Socket_->getRemotePort());

        Http::sendGetRequest(mp1Socket_, host.c_str(), uri);
        return;
    } else if (connId == serviceSocket_->getSocketId()) {
        //TODO informare VehicleControlApp che il servizio è disponibile
        EV_INFO << "Service connection established" << endl;
        //sendPOST schedule was here!
    }
}


void VirtualVehicleMECApp::handleHttpMessage(int connId)
{
    if (mp1Socket_ != nullptr && connId == mp1Socket_->getSocketId()) {
        handleMp1Message(connId);
    }
    else                // if (connId == serviceSocket_->getSocketId())
    {
        handleServiceMessage(connId);
    }
}

void VirtualVehicleMECApp::initializeVirtualVehicleStatus(Packet *packet){
    auto startPk = packet->peekAtFront<VehicleStartPacket>();
    vehicleLength = startPk->getVehicleLength();
    physicalId = startPk->getSumoCarId();
    carId = startPk->getCarId();
    speed = startPk->getSpeed();
    acceleration = startPk->getAcceleration();
    posX = startPk->getPosition_x();
    posY = startPk->getPosition_y();
    posZ = startPk->getPosition_z();
    distance = startPk->getDistance();
    frontVehicle = startPk->getFrontVehicle();
    creationTime = startPk->getCreationTime().dbl();
    sequenceNumber = startPk->getSequenceNumber();
    if (distance == -1.0)
        frontVehicle = "-1";
    lastStatusReceived = startPk->getCreationTime();
    lastStatusArrival = simTime();
}


bool VirtualVehicleMECApp::updateVirtualVehicleStatus(Packet *packet){
    auto statusPk = packet->peekAtFront<VehicleStatusPacket>();
    EV_INFO << "VirtualVehicleMECApp---Status received with age of info: " << simTime() - statusPk->getCreationTime() << endl;
    emit(statusAgeOfInfoSignal, (simTime() - statusPk->getCreationTime()).dbl());

    // check if update is required
    if (statusPk->getCreationTime() < lastStatusReceived) {
        EV << "VirtualVehicleMECApp::handleUeMessage --- Status too old, discarded" << endl;
        emit(statusDiscardedSignal, true);
        return false;
    }
    if (simTime() < lastStatusArrival + minStatusDistance) {
        EV << "VirtualVehicleMECApp::handleUeMessage --- Status has been queued, discarded" << endl;
        emit(statusDiscardedSignal, true);
        return false;
    }

    emit(statusDiscardedSignal, false);
    lastStatusReceived = statusPk->getCreationTime();
    lastStatusArrival = simTime();
    if (strcmp(platoonCarId.c_str(), "") == 0)
        return false;     //Skipping because platoon is not ready
    speed = statusPk->getSpeed();
    acceleration = statusPk->getAcceleration();
    posX = statusPk->getPosition_x();
    posY = statusPk->getPosition_y();
    posZ = statusPk->getPosition_z();
    distance = statusPk->getDistance();
    frontVehicle = statusPk->getFrontVehicle();
    creationTime = statusPk->getCreationTime().dbl();
    sequenceNumber = statusPk->getSequenceNumber();
    desiredAcc = statusPk->getDesiredAcceleration();
    if (distance == -1.0)
        frontVehicle = "-1";
    EV << "Speed: " << speed << "\tAcceleration: " << acceleration << endl;

    return true;

}


//Communication with VehicleControlApp
void VirtualVehicleMECApp::handleUeMessage(omnetpp::cMessage *msg) {
    EV_INFO << "handleUeMessage" << endl;
    auto packet = check_and_cast<Packet *>(msg);
    ueAppAddress = packet->getTag<L3AddressInd>()->getSrcAddress();
    ueAppPort = packet->getTag<L4PortInd>()->getSrcPort();

    auto mecPk = packet->peekAtFront<VehicleControlPacket>();

    if (strcmp(mecPk->getType(), STOP) == 0) {
        //Stop packet
        //TODO chiusura servizi
    } else if ((strcmp(mecPk->getType(), START) == 0) && !serviceAddress.isUnspecified()) {
        initializeVirtualVehicleStatus(packet);
        sendPOST(); //scheduleAt(simTime(), new cMessage("sendPOST"));
        if (!sendStartAckPacket_->isScheduled())
            scheduleAt(simTime() + 0.2, sendStartAckPacket_);
    } else if (strcmp(mecPk->getType(), STATUS) == 0) {
        if (sendStartAckPacket_->isScheduled())
            cancelEvent(sendStartAckPacket_);

        if(updateVirtualVehicleStatus(packet)){
            sendPUT();  // send PUT request to service only if data is new
        }
        //        scheduleAt(simTime(), new cMessage("sendPUT"));
    }


}
void VirtualVehicleMECApp::sendInstructionMessage() {
    auto inst = inet::makeShared<VehicleInstructionPacket>();
    inet::Packet *pk = new inet::Packet("VehicleInstructionPacket");
    inst->setThisAoi(thisAoi);
    inst->setPrecedingAoi(precedingAoi);
    inst->setLeaderAoi(leaderAoi);
    inst->setAcceleration(instructionAcceleration);
    inst->setIsLeader(isLeader);
    inst->setType(INSTRUCTION);
    inst->setChunkLength(inet::B(par("instructionPacketSize")));
    inst->setCreationTime(simTime());
    inst->setSequenceNumber(sequenceNumber); //rtt and packet drop reasons
    inst->setTriggeringCarId(instructionTriggeringCarId.c_str());
    pk->insertAtBack(inst);
    ueSocket.sendTo(pk, ueAppAddress, ueAppPort);
}
void VirtualVehicleMECApp::sendStartAckPacket() {
    auto start = inet::makeShared<VehicleControlPacket>();
    inet::Packet *pk = new inet::Packet("VehicleControlPacketStartAck");
    start->setType(START_ACK);
    start->setChunkLength(inet::B(200));
    pk->insertAtBack(start);
    ueSocket.sendTo(pk, ueAppAddress, ueAppPort);
    //    scheduleAt(simTime() + startAckTimeout_, sendStartAckPacket_);
    scheduleAfter(startAckTimeout_, sendStartAckPacket_);
}
//Communication with service
void VirtualVehicleMECApp::handleMp1Message(int connId) {
    HttpMessageStatus *msgStatus = (HttpMessageStatus*) mp1Socket_->getUserData();
    mp1HttpMessage = (HttpBaseMessage*) msgStatus->httpMessageQueue.front();
    EV << "VirtualVehicleMECApp::handleMp1Message - payload: " << mp1HttpMessage->getBody() << endl;

    try {
        nlohmann::json jsonBody = nlohmann::json::parse(mp1HttpMessage->getBody());
        if (!jsonBody.empty()) {
            jsonBody = jsonBody[0];
            std::string serName = jsonBody["serName"];
            if (serName.compare("PlatoonService") == 0) {
                if (jsonBody.contains("transportInfo")) {
                    nlohmann::json endPoint = jsonBody["transportInfo"]["endPoint"]["addresses"];
                    EV << "address: " << endPoint["host"] << " port: " << endPoint["port"] << endl;
                    std::string address = endPoint["host"];
                    serviceAddress = L3AddressResolver().resolve(address.c_str());

                    servicePort = endPoint["port"];
                    serviceSocket_ = addNewSocket();
                    connect(serviceSocket_ , serviceAddress, servicePort);

                    //                    cMessage *m = new cMessage("connectService");
                    //                    scheduleAt(simTime() + 0.005, m);
                }
            } else {
                EV
                << "VirtualVehicleMECApp::handleMp1Message - PlatoonService not found"
                << endl;
                serviceAddress = L3Address();
            }
        }

    } catch (nlohmann::detail::parse_error *e) {
        EV << e->what() << std::endl;
        // body is not correctly formatted in JSON, manage it
        return;
    }

}
void VirtualVehicleMECApp::handleServiceMessage(int connId) {
    HttpBaseMessage *serviceHttpMessage = nullptr;
    HttpMessageStatus *msgStatus = (HttpMessageStatus*) serviceSocket_->getUserData();
    serviceHttpMessage = (HttpBaseMessage*) msgStatus->httpMessageQueue.front();

    EV << "VirtualVehicleMECApp::HandleServiceMessage---MESSAGGIO RICEVUTO DA SERVIZIO!!!" << endl;
    if (serviceHttpMessage->getType() == RESPONSE) {
        HttpResponseMessage *rspMsg = dynamic_cast<HttpResponseMessage*>(serviceHttpMessage);
        if (rspMsg->getCode() == 204) {
            // in response to a DELETE
            //TODO utilizzare nuovo control packet (STOPACK)
        } else if (rspMsg->getCode() == 201) {
            EV << "VirtualVehicleMECApp::HandleServiceMessage---POST responded"
                    << endl;
            //in response to a POST
            nlohmann::json jsonBody;
            try {
                jsonBody = nlohmann::json::parse(rspMsg->getBody()); // get the JSON structure
                platoonId = jsonBody["platoonId"];
                platoonCarId = jsonBody["carId"];
                sendPlatoonInfoToUe();

            } catch (nlohmann::detail::parse_error *e) {
                EV << e->what() << endl;
                // body is not correctly formatted in JSON, manage it
                return;
            }
        } else if (rspMsg->getCode() == 200) {
            EV << "VirtualVehicleMECApp::HandleServiceMessage---PUT responded"
                    << endl;
            //in response to a PUT
            nlohmann::json jsonBody;
            try {
                EV_INFO << rspMsg->getBody() << endl;
                jsonBody = nlohmann::json::parse(rspMsg->getBody()); // get the JSON structure
                isLeader = jsonBody["isLeader"];
                if (!isLeader){
                    EV_INFO << "Instruction acc: " << jsonBody["acceleration"] << endl;
                    instructionAcceleration = jsonBody["acceleration"];
                    thisAoi = jsonBody["thisAoi"];
                    precedingAoi = jsonBody["precedingAoi"];
                    leaderAoi = jsonBody["leaderAoi"];
                    instructionTriggeringCarId = jsonBody["triggeringCarId"];
                }
                sendInstructionMessage();
            } catch (nlohmann::detail::parse_error *e) {
                EV << e->what() << endl;
                //No acceleration for this vehicle (Probably this is a leader)
                return;
            }
        }
    } else if (serviceHttpMessage->getType() == REQUEST) {
        HttpRequestMessage *reqMsg = dynamic_cast<HttpRequestMessage*>(serviceHttpMessage);
        if (strcmp(reqMsg->getMethod(), "PUT") == 0) {
            EV << "VirtualVehicleMECApp::HandleServiceMessage---Request received" << endl;
            nlohmann::json jsonBody;
            try {
                jsonBody = nlohmann::json::parse(reqMsg->getBody()); // get the JSON structure
            } catch (nlohmann::detail::parse_error *e) {
                EV << e->what() << endl;
                // body is not correctly formatted in JSON, manage it
                return;
            }
            isLeader = jsonBody["isLeader"];
            sequenceNumber = -1; //perché riceviamo pacchetto dal servizio senza aver fatto richiesta

            if (!isLeader){
                EV << "Instruction acc: " << jsonBody["acceleration"] << endl;
                instructionAcceleration = jsonBody["acceleration"];
                thisAoi = jsonBody["thisAoi"];
                precedingAoi = jsonBody["precedingAoi"];
                leaderAoi = jsonBody["leaderAoi"];
                instructionTriggeringCarId = jsonBody["triggeringCarId"];
            }

            EV  << "VirtualVehicleMECApp::HandleServiceMessage---New acceleration: " << instructionAcceleration << endl;
//            scheduleAt(simTime(), new cMessage("sendInstruction"));

            Http::send200Response(serviceSocket_, "New Acceleration OK");
        }
    }

}

void VirtualVehicleMECApp::sendPlatoonInfoToUe() {
    auto pi = inet::makeShared<VehiclePlatoonInfoPacket>();
    Packet *packet = new Packet(PLATOON_INFO);
    pi->setPlatoonCarId(platoonCarId.c_str());
    pi->setPlatoonId(platoonId.c_str());
    pi->setChunkLength(inet::B(200)); //TODO: da definire
    pi->setCreationTime(simTime());
    packet->insertAtBack(pi);
    ueSocket.sendTo(packet, ueAppAddress, ueAppPort);

}

void VirtualVehicleMECApp::sendPUT() {
    nlohmann::json jsonBody;
    jsonBody["platoonId"] = platoonId;
    jsonBody["platoonCarId"] = platoonCarId;
    jsonBody["speed"] = speed;
    jsonBody["acceleration"] = acceleration;
    jsonBody["posX"] = posX;
    jsonBody["posY"] =  posY;
    jsonBody["posZ"]= posZ;
    jsonBody["distance"] = distance;
    jsonBody["frontVehicle"] = frontVehicle;
    jsonBody["sequenceNumber"] = sequenceNumber;
    jsonBody["dataCreatedAt"] = creationTime;

    EV << "PUT BODY: " << jsonBody << endl;

    std::string uri = "/example/Platoon/v1/subscriptions/vehicle";
    std::string host = serviceSocket_->getRemoteAddress().str() + ":"
            + std::to_string(serviceSocket_->getRemotePort());
    Http::sendPutRequest(serviceSocket_, jsonBody.dump().c_str(), host.c_str(), uri.c_str());
}
void VirtualVehicleMECApp::sendPOST() {
    std::string uri = "/example/Platoon/v1/subscriptions/vehicle";
    std::string host = serviceSocket_->getRemoteAddress().str() + ":"
            + std::to_string(serviceSocket_->getRemotePort());

    nlohmann::json jsonBody;
    jsonBody["physicalId"]= physicalId;
    jsonBody["carId"] = carId;
    jsonBody["speed"] = speed;
    jsonBody["acceleration"] = acceleration;
    jsonBody["posX"] = posX;
    jsonBody["posY"] = posY;
    jsonBody["posZ"] = posZ;
    jsonBody["distance"] = distance;
    jsonBody["frontVehicle"] = frontVehicle;
    jsonBody["vehicleLength"] = vehicleLength;
    jsonBody["sequenceNumber"] = sequenceNumber;
    jsonBody["dataCreatedAt"] =  creationTime;

    EV << "POST BODY: " << jsonBody << endl;
    Http::sendPostRequest(serviceSocket_, jsonBody.dump().c_str(), host.c_str(), uri.c_str());
    EV << "POST SENT";
}
