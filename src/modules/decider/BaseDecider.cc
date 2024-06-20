//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "BaseDecider.h"
#include "inet/common/packet/Packet.h"

#include "veins_inet/VeinsInetMobility.h"

#define AVERAGE_CQI_UL_SIGNAL_NAME "averageCqiUl"
#define AVERAGE_CQI_DL_SIGNAL_NAME "averageCqiDl"
#define ACCELERATION_CONTROLLER_SIGNAL_NAME "accelerationSignal"
#define SPEED_CONTROLLER_SIGNAL_NAME "speedSignal"
#define DISTANCE_CONTROLLER_SIGNAL_NAME "distanceSignal"
#define PACKET_PULLED_SIGNAL_NAME "packetPulled"



void BaseDecider::initialize(int stage)
{
    if (stage != DECIDER_LOCAL_STAGE)
        return;

    accelerationSignal = registerSignal("accelerationSignal");
    speedSignal = registerSignal("speedSignal");
    distanceErrorSignal = registerSignal("distanceErrorSignal");

    cellularCqiUlSignal = registerSignal("cellularCqiUlSignal");
    cellularCqiDlSignal = registerSignal("cellularCqiDlSignal");
    cellularRttSignal = registerSignal("cellularRttSignal");

    cellularThisVehicleAoiSignal = registerSignal("cellularThisVehicleAoiSignal");
    cellularPrecedingVehicleAoiSignal = registerSignal("cellularPrecedingVehicleAoiSignal");
    cellularLeaderVehicleAoiSignal = registerSignal("cellularLeaderVehicleAoiSignal");
    cellularInstructionAoiSignal = registerSignal("cellularInstructionAoiSignal");

    dsrcPrecedingVehicleAoiSignal = registerSignal("dsrcPrecedingVehicleAoiSignal");
    dsrcLeaderVehicleAoiSignal = registerSignal("dsrcLeaderVehicleAoiSignal");


    dsrcMacQueueingTimeSignal = registerSignal("dsrcMacQueueingTimeSignal");


    cellularInstructionDifferenceSignal = registerSignal("cellularInstructionDifferenceSignal");
    dsrcInstructionDifferenceSignal = registerSignal("dsrcInstructionDifferenceSignal");

    // used system and instruction signal
    decisionSystemSignal = registerSignal("decisionSystemSignal");
    decisionInstructionSignal = registerSignal("decisionInstructionSignal");

    getModuleByPath("^.cellularNic")->subscribe(AVERAGE_CQI_UL_SIGNAL_NAME, this);
    getModuleByPath("^.cellularNic")->subscribe(AVERAGE_CQI_DL_SIGNAL_NAME, this);

    getModuleByPath("^.v2vNic.mac.dcf.channelAccess.pendingQueue")->subscribe(PACKET_PULLED_SIGNAL_NAME, this);

    getModuleByPath("^.controller")->subscribe(ACCELERATION_CONTROLLER_SIGNAL_NAME, this);
    getModuleByPath("^.controller")->subscribe(SPEED_CONTROLLER_SIGNAL_NAME, this);
    getModuleByPath("^.controller")->subscribe(DISTANCE_CONTROLLER_SIGNAL_NAME, this);

    physicalCarId = veins::VeinsInetMobilityAccess().get(getParentModule())->getExternalId();
    carId = getParentModule()->getFullName();
    //targetDistance = par("targetDistance").doubleValue();
    controlLawModule = check_and_cast<ControlLaw*>(getModuleByPath("^.controlLaw"));
    lowLevelController = check_and_cast<LowLevelController*>(getModuleByPath("^.controller"));


}

double BaseDecider::getTargetDistanceFromControlLaw(){
    return controlLawModule->getTargetDistance(lowLevelController->getStatus(false));
}


void BaseDecider::receiveSignal(cComponent *src, simsignal_t signalId, double value, cObject *details){
    Enter_Method_Silent("receiveSignal");

    auto signalName = getSignalName(signalId);

    //EV_DEBUG << "DECIDER received signal " << signalName << " from " << src->getName() <<endl;

    if (strcmp(src->getName(),"controller")==0){
        if (strcmp(signalName, ACCELERATION_CONTROLLER_SIGNAL_NAME) == 0){
            emit(accelerationSignal, value);
            registerValue("acceleration", simTime().dbl(), value);
        }
        if (strcmp(signalName, SPEED_CONTROLLER_SIGNAL_NAME) == 0){
            emit(speedSignal, value);
            registerValue("speed", simTime().dbl(), value);
        }
        if (strcmp(signalName, DISTANCE_CONTROLLER_SIGNAL_NAME) == 0){
            auto targetDistance = getTargetDistanceFromControlLaw();
            emit(distanceErrorSignal, value - targetDistance);
            registerValue("distanceError", simTime().dbl(), value -targetDistance);
        }
    }
    else {
        if (strcmp(signalName, AVERAGE_CQI_UL_SIGNAL_NAME) == 0){
            emit(cellularCqiUlSignal, value);
            registerValue("cellularCqiUl", simTime().dbl(), value);
        }

        if (strcmp(signalName, AVERAGE_CQI_DL_SIGNAL_NAME) == 0){
            emit(cellularCqiDlSignal, value);
            registerValue("cellularCqiDl", simTime().dbl(), value);
        }
    }

}

void BaseDecider::receiveSignal(cComponent *src, simsignal_t signalId, cObject *obj, cObject *details){
    Enter_Method_Silent("receiveSignal");
    auto signalName = getSignalName(signalId);
    if (strcmp(src->getName(),"pendingQueue")==0){
        if (strcmp(signalName, PACKET_PULLED_SIGNAL_NAME) == 0){
           auto pkt = check_and_cast<inet::Packet*>(obj);
           double queueingTime = (simTime() - pkt->getArrivalTime()).dbl();
           emit(dsrcMacQueueingTimeSignal, queueingTime);
           registerValue("dsrcMacQueueingTime", simTime().dbl(), queueingTime);
        }

    }
}


void BaseDecider::addCellularRttValue(double v){
    emit(cellularRttSignal, v);
    registerValue("cellularRtt", simTime().dbl(), v);
}

void BaseDecider::addCellularThisVehicleAoiValue(double v) {
    emit(cellularThisVehicleAoiSignal, v);
    registerValue("cellularThisVehicleAoi", simTime().dbl(), v);
}

void BaseDecider::addCellularPrecedingVehicleAoiValue(double v) {
    emit(cellularPrecedingVehicleAoiSignal, v);
    registerValue("cellularPrecedingVehicleAoi", simTime().dbl(), v);
}

void BaseDecider::addCellularLeaderVehicleAoiValue(double v) {
    emit(cellularLeaderVehicleAoiSignal, v);
    registerValue("cellularLeaderVehicleAoi", simTime().dbl(), v);
}

void BaseDecider::addCellularInstructionAoiValue(double v) {
    emit(cellularInstructionAoiSignal, v);
    registerValue("cellularInstructionAoi", simTime().dbl(), v);
}

void BaseDecider::addCellularInstruction(double instruction){
    double idealInstruction = controlLawModule->computeLawUsingSensorData(physicalCarId);
    emit(cellularInstructionDifferenceSignal, instruction - idealInstruction);
    registerValue("cellularInstructionDifference", simTime().dbl(), instruction - idealInstruction);
}

void BaseDecider::addDsrcPrecedingVehicleAoiValue(double v){
    emit(dsrcPrecedingVehicleAoiSignal, v);
    registerValue("dsrcPrecedingVehicleAoi", simTime().dbl(), v);
}
void BaseDecider::addDsrcLeaderVehicleAoiValue(double v){
    emit(dsrcLeaderVehicleAoiSignal, v);
    registerValue("dsrcLeaderVehicleAoi", simTime().dbl(), v);
}


void BaseDecider::addDsrcAccelarationInstruction(double instruction){
    double idealInstruction = controlLawModule->computeLawUsingSensorData(physicalCarId);
    emit(dsrcInstructionDifferenceSignal,instruction - idealInstruction);
    registerValue("dsrcInstructionDifference", simTime().dbl(), instruction - idealInstruction);
}


bool BaseDecider::isCellularReliable(){
    //TODO more complex if needed
    return cellularReliabilityLevel == RATReliabilityLevel::HIGH;
    //return false;

}
bool BaseDecider::isDsrcReliable(){
    //TODO more complex if needed
    return dsrcReliabilityLevel == RATReliabilityLevel::HIGH;
}


void BaseDecider::registerUsedInstruction(instruction_t instruction){
    emit(decisionInstructionSignal, instruction.instruction);
    emit(decisionSystemSignal, (int) instruction.systemType);
}


void BaseDecider::evaluateAllRatReliability(){
    if (simTime() - lastRatEvaluationTime >= par("minRatEvaluationInterval").doubleValue()){
        evaluateCellularRatReliability();
        evaluateDsrcRatReliability();
        lastRatEvaluationTime = simTime();
    }
}
