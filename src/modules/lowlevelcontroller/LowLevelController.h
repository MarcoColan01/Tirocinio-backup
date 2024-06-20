#ifndef __LOWLEVELCONTROLLER_H_
#define __LOWLEVELCONTROLLER_H_

#include "math.h"
#include "omnetpp.h"
#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetMobility.h"
#include "veins_inet/VeinsInetManager.h"
#include "common/types_t.h"
#include "apps/packets/VehicleControlPacket_m.h"
#include "apps/packets/VehicleControlPacket_Types.h"
#include "veins/modules/utility/SignalManager.h"
#include "modules/extendedveins/ExtendedVeinsInetMobility.h"

#include "LeaderSpeedPattern.h"
#include "sumo/engine/GenericEngineModel.h"


using namespace omnetpp;
using namespace inet;

#define FIRST_ORDER_LAG_ENGINE "first_order_lag"
#define NO_LAG_ENGINE "no_lag"



class LowLevelController : public cSimpleModule{
    double betaAccel;
    double betaDecel;
    double desiredAccel;
    double updatePeriod;
    double timeStepInterval;
    double maxSpeed;
    bool accelSet;
    bool useActuationLag;
    double interInstructionsMaxTime;
    simtime_t lastInstructionTimestamp;

    LeaderSpeedPattern * leaderSpeedPattern;


    simsignal_t speedSignal;
    simsignal_t accelerationSignal;
    simsignal_t distanceSignal;
    simsignal_t posXSignal;
    simsignal_t posYSignal;
    simsignal_t posZSignal;

    veins::VeinsInetMobility* mobility;
    veins::ExtendedVehicle* commandInterface;
    veins::SignalManager veinsSignalManager;

//    cMessage *updateMessage;
    cMessage *speedPatternStartMessage;

    bool firstExecuteStep = true;

public:
    LowLevelController();
    ~LowLevelController();
    void setAcceleration(double accel);
    double getVehicleLength();

    /**
     * Returns the status_t of this LowLevelController.
     * The parameter emitStats allows to emit the status_t if it's true, which is the default behaviour.
     */
    status_t getStatus(bool emitStats = true);

    void setSafeSpeed(bool value);
    void setUseActuationLag(bool value);
protected:
    void initialize(int stage);
    virtual int numInitStages() const {return inet::NUM_INIT_STAGES;}
    virtual void handleMessage(cMessage* msg);
    void executeStep();
//    void sendUpdates();
    double actuationLag();

    void initializeEngine();


    std::string vehicleEngineFile;
    std::string vehicleEngineType;
    GenericEngineModel *engineModel = nullptr;

};
#endif
