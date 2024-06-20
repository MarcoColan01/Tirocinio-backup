#include <math.h>
#include "LowLevelController.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/FlatTransmitterBase.h"
#include "sumo/engine/FirstOrderLagModel.h"
#include "sumo/engine/RealisticEngineModel.h"
#include "sumo/engine/NoLagModel.h"
#include "sumo/CC_Const.h"

Define_Module(LowLevelController);



LowLevelController::LowLevelController() {}
LowLevelController::~LowLevelController() {
    //    cancelAndDelete(updateMessage);
}

void LowLevelController::initialize(int stage){
    cSimpleModule::initialize(stage);

    if(stage == INITSTAGE_LOCAL){
        //retrieve parameters
        updatePeriod = par("updatePeriod");
        betaAccel = par("betaAcceleration");
        betaDecel = par("betaDeceleration");

        accelerationSignal = registerSignal("accelerationSignal");
        distanceSignal = registerSignal("distanceSignal");
        speedSignal = registerSignal("speedSignal");
        posXSignal = registerSignal("posXSignal");
        posYSignal = registerSignal("posYSignal");
        posZSignal = registerSignal("posZSignal");

        //mobility
        mobility = veins::VeinsInetMobilityAccess().get(getParentModule());
        commandInterface = static_cast<veins::ExtendedVehicle*>(mobility->getVehicleCommandInterface());
        maxSpeed = commandInterface->getMaxSpeed();
        accelSet = false; //TODO refactor with state pattern!
        interInstructionsMaxTime = par("interInstructionsMaxTime").doubleValue();
        //engine
        vehicleEngineFile = par("vehicleEngineFile").stdstringValue();
        vehicleEngineType = par("vehicleEngineType").stdstringValue();
        useActuationLag = par("useActuationLag");
        //        updateMessage = new cMessage("sendUpdate");
        //        scheduleAt(simTime() + uniform(0, 0.1), updateMessage);

        //lastCheckCollisionSimtime = simTime();

    }
    if(stage == INITSTAGE_LAST){
        commandInterface->setLaneChangeMode(0);
        timeStepInterval = findModuleByPath("<root>.veinsManager")->par("updateInterval").doubleValue();
        initializeEngine();

        leaderSpeedPattern = createLeaderSpeedPattern(this);
        useActuationLag = leaderSpeedPattern->useActuationLag(useActuationLag);
        if (par("hasSpeedPattern").boolValue()){
            //speedPatternStartTime
            speedPatternStartMessage = new cMessage("speedPatternStart");
            scheduleAfter(par("speedPatternStartTime").doubleValue(), speedPatternStartMessage);
        }

        auto timestep = [this](veins::SignalPayload<simtime_t const&>) { executeStep();};
        veinsSignalManager.subscribeCallback(veins::FindModule<veins::VeinsInetManager*>::findGlobalModule(), veins::TraCIScenarioManager::traciTimestepEndSignal, timestep);
        commandInterface->setMinGap(0.0);
        commandInterface->setSpeedMode(30);

        commandInterface->setSpeed(par("expectedSpeed").doubleValue());

    }
}

void LowLevelController::initializeEngine(){
    if (vehicleEngineType.compare(NO_LAG_ENGINE) == 0){
        EV_DEBUG << "No lag Engine" <<endl;
        engineModel = new NoLagModel();
    }
    else if (vehicleEngineType.compare(FIRST_ORDER_LAG_ENGINE) == 0){
        // IDEAL ENGINE (First order lag)
        EV_DEBUG << "Ideal Engine : First order lag" <<endl;
        engineModel = new FirstOrderLagModel();
        engineModel->setParameter(FOLM_PAR_DT, timeStepInterval);
        engineModel->setParameter(FOLM_PAR_TAU, 0.2); //TODO from config
    }
    else{
        // REAL ENGINE
        EV_DEBUG << "Realistic Engine: "<< vehicleEngineType <<endl;
        engineModel = new RealisticEngineModel();
        engineModel->setParameter(ENGINE_PAR_XMLFILE, vehicleEngineFile);
        engineModel->setParameter(ENGINE_PAR_VEHICLE, vehicleEngineType);
        engineModel->setParameter(ENGINE_PAR_DT, timeStepInterval);
    }
}




void LowLevelController::setAcceleration(double accel){
    desiredAccel = accel;
    lastInstructionTimestamp = simTime();
    if(!accelSet){
        accelSet = true;

    }

}


void LowLevelController::handleMessage(cMessage* msg){
    if(msg->isSelfMessage()){
        //        if (msg == updateMessage){
        //            scheduleAt(simTime()+updatePeriod, msg);
        //            sendUpdates();
        //        }else
        if (msg == speedPatternStartMessage){
            EV_DEBUG << "Start leader speed pattern" << endl;
            leaderSpeedPattern->startPattern(simTime().dbl());
            delete msg;
        }

    }
    else
        EV << "LowLevelController::handleMessage --- unrecognized message. Discarded";
}


//void LowLevelController::sendUpdates() {  // TODO refactoring: chiamare la
//    // funzione get status e mandare un
//    // cMessage alla vehicleControlApp
//    inet::Coord pos = mobility->getCurrentPosition();
//    std::pair<std::string, double> frontVehicleInfo = commandInterface->getLeader(10000);
//
//    double acc = commandInterface->getAcceleration();
//    double speed = commandInterface->getSpeed();
//    double posX = pos.getX();
//    double posY = pos.getY();
//    double posZ = pos.getZ();
//    double distance = frontVehicleInfo.second;
//    const char* frontVehicle = frontVehicleInfo.first.c_str();
//
//    emit(accelerationSignal, acc);
//    emit(speedSignal, speed);
//    emit(posXSignal, posX);
//    emit(posYSignal, posY);
//    emit(posZSignal, posZ);
//    emit(distanceSignal, distance);
//    EV << "LOW LEVEL CONTROLLER: sendUpdates" << endl;
//}

void LowLevelController::executeStep()
{
    getStatus();

    Enter_Method("executeStep");
    if (commandInterface->checkCollision()){
        EV << "COLLISION" << endl;
        endSimulation();
    }



    if (firstExecuteStep){
        /*
         * This allows traci to set the expectedSpeed at the first sumo timestep
         * overriding the departSpeed in rou.xml file
         */
        commandInterface->setSpeed(par("expectedSpeed").doubleValue());
        firstExecuteStep = false;
        return;
    }

    double currentSpeed = commandInterface->getSpeed();
    double newSpeed = currentSpeed;
    EV_DEBUG << "accelSet: " << accelSet <<endl;
    if(accelSet){
        double accWithLag = actuationLag();
        //        EV << "New speed " << newSpeed << endl;
        commandInterface->setAcceleration(accWithLag, 1.0);
    } else{ //LEADER
        newSpeed = leaderSpeedPattern->getSpeed(simTime().dbl(), currentSpeed);
        if (useActuationLag){
            desiredAccel = (newSpeed - currentSpeed);
            double accWithLag = actuationLag();
            //            EV_INFO << desiredAccel << " - " << accWithLag << endl;
            commandInterface->setAcceleration(accWithLag, 1.0);
            lastInstructionTimestamp = simTime();
        }
        else{
            commandInterface->setSpeed(std::max(0.0, newSpeed));
        }
    }

}


double LowLevelController::actuationLag(){
    Enter_Method("actuationLag");
    double currentAcceleration = commandInterface->getAcceleration();
    double currentSpeed = commandInterface->getSpeed();

    double checkedDesiredAcceleration = desiredAccel;
    if (simTime() - lastInstructionTimestamp > interInstructionsMaxTime){
        //        emit(controlSuspendedSignal, true);
        checkedDesiredAcceleration = 0.0;
    }

    double acc = engineModel->getRealAcceleration(currentSpeed, currentAcceleration, checkedDesiredAcceleration, timeStepInterval);

    EV << "desired: "<< desiredAccel  << " Checked " << checkedDesiredAcceleration << " Current: "<< currentAcceleration <<" got: " <<acc  << endl;
    return acc;

    //    if(desiredAccel >= 0)
    //        return betaAccel*desiredAccel + (1-betaAccel)*currentAcceleration;
    //    else
    //        return betaDecel*desiredAccel + (1-betaDecel)*currentAcceleration;
}

double LowLevelController::getVehicleLength(){
    return commandInterface->getLength();
}

status_t LowLevelController::getStatus(bool emitStats) {
    status_t status;
    status.acceleration     = commandInterface->getAcceleration();
    status.vehicleLength    = commandInterface->getLength();
    status.speed            = commandInterface->getSpeed();
    status.sumoCarId        = mobility->getExternalId();
    status.carId            = mobility->getParentModule()->getFullName();
    status.desiredAcceleration = desiredAccel;

    inet::Coord pos         = mobility->getCurrentPosition();
    status.position_x       = pos.getX();
    status.position_y       = pos.getY();
    status.position_z       = pos.getZ();

    std::pair<std::string, double> frontVehicleInfo = commandInterface->getLeader(10000);
    status.frontVehicle     = frontVehicleInfo.first;
    status.distance         = frontVehicleInfo.second;
    std::pair<std::string, double> behindVehicleInfo = commandInterface->getFollower(10000);
    status.behindVehicle = behindVehicleInfo.first;
    status.behindDistance = behindVehicleInfo.second;

    //std::cout << status.carId << ": " << status.distance << "-------" << status.position_x << "-------"<< status.frontVehicle   << endl;

    if(emitStats){
        emit(accelerationSignal, status.acceleration);
        emit(speedSignal, status.speed);
        emit(posXSignal, status.position_x );
        emit(posYSignal, status.position_y);
        emit(posZSignal, status.position_z);
        emit(distanceSignal, status.distance);
    }



    return status;
}

void LowLevelController::setSafeSpeed(bool value) {


    if(value)
        commandInterface->setSpeedMode(31);
    else
        commandInterface->setSpeedMode(30);
}
