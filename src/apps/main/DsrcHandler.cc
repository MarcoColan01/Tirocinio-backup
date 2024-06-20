/*
 * OfflineHandler.cc
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#include "DsrcHandler.h"

#include "MainApp.h"
#include "apps/packets/VehicleControlPacket_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211DimensionalTransmitter.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"
#include "omnetpp.h"

using namespace omnetpp;

DsrcHandler::DsrcHandler(const char *platoonId, const char *platoonCarId,
        cModule *parent,
        ControlLaw *controlLaw,
        PowerController *powerController,
        OnboardControlLawMode controlLawMode) {
    this->controlLaw = controlLaw;
    this->platoonId = string(platoonId);
    this->platoonCarId = string(platoonCarId);
    this->vehiclesDataProvider = new SelfVehiclesDataProvider();
    this->powerController = powerController;
    this->parent = parent;
    this->controlLaw->setVehiclesDataProvider(this->vehiclesDataProvider);
    this->controlLawMode = controlLawMode;
    nextMaxPower = false;
    decider = check_and_cast<BaseDecider*>(parent->getParentModule()->getSubmodule("decider"));
}

void DsrcHandler::init(map<int, SocketWrapper *> s) {
    socket = s.find(V2V_SOCKET)->second;
    socket->setCallback(this);
}

bool DsrcHandler::isReady() { return socket != nullptr; }

void DsrcHandler::onNewDataArrived(status_t status) {
    EV << "OfflineHandler::onNewDataArrived: behind vehicle:"
            << status.behindVehicle << " - behind distance: " << status.behindDistance
            << endl;

    // Questa cosa è sbagliata. Per la mia tesi però andava bene.
    // In pratica prendiamo per chiamata diretta la dimensione del platoon.
    // In realtà è l'applicazione MEC a dover comunicare al veicolo la dimensione
    // ogni volta che cambia e se è l'ultimo
    GlobalPlatoonsManager *gpm = check_and_cast<GlobalPlatoonsManager *>(parent->getModuleByPath("<root>.globalPlatoonsManager"));

    isLastVehicleInPlatoon = gpm->isLastVehicle(platoonId, platoonCarId);
    platoonSize = gpm->platoonSize(platoonId);

    EV << "OfflineHandler::onNewDataArrived: lastVehicleInPlatoon="
            << isLastVehicleInPlatoon << " platoonSize=" << platoonSize << endl;

    if (controlLawMode == OnboardControlLawMode::SYNCHRONOUS) {
        computeControlLaw();
    }

    sendStatusUpdate(status);
}



void DsrcHandler::socketDataArrived(UdpSocket *socket, Packet *packet) {
    auto platoonInfo = packet->peekAtFront<VehiclePlatoonInfoPacket>(B(10));
    if (strcmp(platoonInfo->getPlatoonId(), this->platoonId.c_str()) == 0) {
        auto status = packet->peekAtBack<VehicleStatusPacket>(B(200));
        string uniqueId(platoonInfo->getPlatoonId());
        uniqueId.append(platoonInfo->getPlatoonCarId());
        vehicle_t data;
        data.desiredAcceleration = status->getDesiredAcceleration();
        data.acceleration = status->getAcceleration();
        data.platoonCarId = platoonInfo->getPlatoonCarId();
        data.distance = status->getDistance();
        data.speed = status->getSpeed();
        data.creationTime = status->getCreationTime().dbl();
        vehiclesDataProvider->addVehicle(data);
        EV << "OfflineHandler::socketDataArrived: car uniqueId=" << platoonId << platoonCarId << endl
                << "Known cars: ";
        vehiclesDataProvider->print();


        if (controlLawMode == OnboardControlLawMode::ASYNCHRONOUS &&
                dependOnVehicle(platoonInfo->getPlatoonCarId())){
            EV_INFO << "OfflineHandler::socketDataArrived Useful data arrived from: " << platoonInfo->getPlatoonId() << platoonInfo->getPlatoonCarId() << endl;
            computeControlLaw();
        }

    }
    delete packet;
}


void DsrcHandler::sendStatusUpdate(status_t status){
    auto statusPk = inet::makeShared<VehicleStatusPacket>();
    statusPk->setType(STATUS);
    statusPk->setPosition_x(status.position_x);
    statusPk->setPosition_y(status.position_y);
    statusPk->setPosition_z(status.position_z);
    statusPk->setAcceleration(status.acceleration);
    statusPk->setSpeed(status.speed);
    statusPk->setDistance(status.distance);
    statusPk->setFrontVehicle(status.frontVehicle.c_str());
    statusPk->setCreationTime(simTime());
    statusPk->setChunkLength(inet::B(200));
    statusPk->setDesiredAcceleration(status.desiredAcceleration);

    auto pi = inet::makeShared<VehiclePlatoonInfoPacket>();
    pi->setPlatoonCarId(platoonCarId.c_str());
    pi->setPlatoonId(platoonId.c_str());
    pi->setChunkLength(inet::B(10));
    pi->addTagIfAbsent<inet::CreationTimeTag>()->setCreationTime(simTime());

    auto packet = unique_ptr<Packet>(new Packet(("Data" + platoonId + platoonCarId).c_str()));
    packet->insertAtFront(pi);
    packet->insertAtBack(statusPk);
    socket->send(move(packet).release());
}

void DsrcHandler::computeControlLaw(){
    if (onNewVehiclePacketListener != nullptr &&       // If it's null, it means that platoon information has not arrived yet
            isFollower() &&
            hasAllRequiredVehicleData()){
        double accelerationInstruction = controlLaw->computeLaw(this->platoonCarId);
        // register new values to decider
        decider->addDsrcAccelarationInstruction(accelerationInstruction);

//        cout << this->platoonCarId << " " <<vehiclesDataProvider->getAoIVehicleData(0, simTime().dbl()) << endl;
        decider->addDsrcLeaderVehicleAoiValue(vehiclesDataProvider->getAoIVehicleData(0, simTime().dbl()));
        decider->addDsrcPrecedingVehicleAoiValue(vehiclesDataProvider->getAoIVehicleData(stoi(this->platoonCarId) -1, simTime().dbl()));

        vehicle_instruction_t instr = {isLeader(), accelerationInstruction};
        onNewVehiclePacketListener->onNewInstructionReceived(this, instr);
    }
}
