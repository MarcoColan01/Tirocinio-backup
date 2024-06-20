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

#ifndef __SIMULATOR_5G_V2X_BASEDECIDER_H_
#define __SIMULATOR_5G_V2X_BASEDECIDER_H_

#include <omnetpp.h>

#include "common/types_t.h"
#include "modules/controlLaw/ControlLaw.h"
#include "modules/lowlevelcontroller/LowLevelController.h"
#include "common/multiRat.h"

using namespace omnetpp;
using namespace multirat;



class BaseDecider : public cSimpleModule, cListener
{

private:
    ControlLaw *controlLawModule;
    LowLevelController *lowLevelController;
    simtime_t lastRatEvaluationTime;
    double getTargetDistanceFromControlLaw();

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return DECIDER_BASE_NUM_INIT_STAGES; }

    // base implementation does nothing
    virtual void registerValue(std::string featureName, double simtime, double value) {}
    virtual void evaluateCellularRatReliability() {}
    virtual void evaluateDsrcRatReliability() {}
    //    virtual RATReliabilityLevel

    //double targetDistance;
    std::string carId;
    std::string physicalCarId;
    RATReliabilityLevel cellularReliabilityLevel = RATReliabilityLevel::HIGH  ;
    RATReliabilityLevel dsrcReliabilityLevel = RATReliabilityLevel::HIGH;


    simsignal_t accelerationSignal;
    simsignal_t speedSignal;
    simsignal_t distanceErrorSignal;

    simsignal_t cellularCqiUlSignal;
    simsignal_t cellularCqiDlSignal;
    simsignal_t cellularRttSignal;

    simsignal_t cellularThisVehicleAoiSignal;
    simsignal_t cellularPrecedingVehicleAoiSignal;
    simsignal_t cellularLeaderVehicleAoiSignal;
    simsignal_t cellularInstructionAoiSignal;
    simsignal_t dsrcPrecedingVehicleAoiSignal;
    simsignal_t dsrcLeaderVehicleAoiSignal;

    simsignal_t dsrcMacQueueingTimeSignal;


    simsignal_t cellularInstructionDifferenceSignal;
    simsignal_t dsrcInstructionDifferenceSignal;

    simsignal_t decisionSystemSignal;
    simsignal_t decisionInstructionSignal;


public:
    string getPhysicalCarId(){return physicalCarId;}

    void addCellularThisVehicleAoiValue(double v);
    void addCellularPrecedingVehicleAoiValue(double v);
    void addCellularLeaderVehicleAoiValue(double v);
    void addCellularInstructionAoiValue(double v);
    void addCellularRttValue(double v);
    void addCellularInstruction(double v);

//    void addDsrcThisVehicleAoiValue(double v);
    void addDsrcPrecedingVehicleAoiValue(double v);
    void addDsrcLeaderVehicleAoiValue(double v);
    void addDsrcAccelarationInstruction(double v);

    void receiveSignal(cComponent *src, simsignal_t signalId, double value, cObject *details);
    void receiveSignal(cComponent *src, simsignal_t signalId, cObject *obj, cObject *details);

    virtual void evaluateAllRatReliability();

    void registerUsedInstruction(instruction_t instruction);
    bool isCellularReliable();
    bool isDsrcReliable();

};

#endif
