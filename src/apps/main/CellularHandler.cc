/*
 * OnlineHandler.cpp
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#include "CellularHandler.h"

#include "MainApp.h"
#include "apps/packets/PlatoonInfo_Types.h"
#include "omnetpp.h"

using namespace omnetpp;

void CellularHandler::init(map<int, SocketWrapper *> s) {
    socket = s.find(MEC_SOCKET)->second;
    socket->setCallback(this);
}

bool CellularHandler::isReady() { return socket != nullptr; }

void CellularHandler::onNewDataArrived(status_t status) {
    //Il prima pacchetto è diverso.
    //Non ricordo perché, ma quelli prima avevano fatto così
    if (platoonRegistered){
        createAndSendStatusPacket(status);
    }else{
//        vehiclePlatoonLogicRegistration(status);
        createAndSendPlatoonRegisterPacket(status);
    }
    sequenceTime[sequenceNumber++] = simTime().dbl();
    EV_INFO << "CellularHandler::onNewDataArrived: status sent " << simTime() << endl;
}

void CellularHandler::socketDataArrived(UdpSocket *socket, Packet *packet) {
    //    firstPacket = false; //Stiamo assumendo che vada al primo colpo. TODO: handle dell'ACK
    if (strcmp(packet->getName(), PLATOON_INFO) == 0) {
        platoonRegistered = true;
        auto pi = packet->peekAtFront<VehiclePlatoonInfoPacket>();
        onNewVehiclePacketListener->onPlatoonInfoReceived(this, pi.get());
    } else {
        auto mecPkt = packet->peekAtFront<VehicleControlPacket>();
        if (strcmp(mecPkt->getType(), INSTRUCTION) == 0) {
            //qui si potrebbe separare
            auto instr = dynamicPtrCast<const VehicleInstructionPacket>(mecPkt);
            int seqNumber = instr->getSequenceNumber();
            if(seqNumber != -1){
                EV_DEBUG << "seq num: " << seqNumber << " triggered by: "<< instr->getTriggeringCarId() << " RTT:" << simTime().dbl() - sequenceTime[seqNumber] << endl;
                decider->addCellularRttValue(simTime().dbl() - sequenceTime[seqNumber]);
                sequenceTime.erase(seqNumber);
                EV_DEBUG << "============= REMAINING SEQ NUMBER:" << endl;
                for(auto it = sequenceTime.begin(); it != sequenceTime.end(); it++)
                    EV_DEBUG << it->first << endl;
                EV_DEBUG << "===================================" << endl;
            }
            decider->addCellularThisVehicleAoiValue(instr->getThisAoi());
            decider->addCellularPrecedingVehicleAoiValue(instr->getPrecedingAoi());
            decider->addCellularLeaderVehicleAoiValue(instr->getLeaderAoi());
            decider->addCellularInstructionAoiValue(simTime().dbl() - instr->getCreationTime().dbl());
            decider->addCellularInstruction(instr->getAcceleration());



            if(onNewVehiclePacketListener != nullptr)
                onNewVehiclePacketListener->onNewInstructionReceived(this, instr.get());
        }
    }
    delete packet;
}


void CellularHandler::createAndSendPlatoonRegisterPacket(status_t status) {
    Packet *packet = new Packet("VehicleControlPacketStart");
    auto start = makeShared<VehicleStartPacket>();
    start->setType(START);
    start->setCarId(status.carId.c_str());
    start->setSumoCarId(status.sumoCarId.c_str());
    start->setVehicleLength(status.vehicleLength);
    start->setSpeed(status.speed);
    start->setAcceleration(status.acceleration);
    start->setDistance(status.distance);
    start->setFrontVehicle(status.frontVehicle.c_str());
    start->setDesiredAcceleration(status.desiredAcceleration);
    start->setPosition_x(status.position_x);
    start->setPosition_y(status.position_y);
    start->setPosition_z(status.position_z);
    start->setCreationTime(simTime());
    start->setSequenceNumber(sequenceNumber);
    start->setChunkLength(inet::B(200));  // TODO mettere la dimensione corretta
    packet->insertAtBack(start);
    socket->send(packet);
}

void CellularHandler::createAndSendStatusPacket(status_t status) {
    inet::Packet *packet = new inet::Packet("VehicleStatusPacket");
    auto pk = inet::makeShared<VehicleStatusPacket>();
    pk->setType(STATUS);
    pk->setPosition_x(status.position_x);
    pk->setPosition_y(status.position_y);
    pk->setPosition_z(status.position_z);
    pk->setAcceleration(status.acceleration);
    pk->setSpeed(status.speed);
    pk->setDistance(status.distance);
    pk->setFrontVehicle(status.frontVehicle.c_str());
    pk->setCreationTime(simTime());
    pk->setSequenceNumber(sequenceNumber);
    pk->setChunkLength(inet::B(200));
    pk->setDesiredAcceleration(status.desiredAcceleration);
    packet->insertAtBack(pk);
    socket->send(packet);
}

