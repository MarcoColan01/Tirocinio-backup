#include "GlobalPlatoonsManager.h"

#include "modules/extendedveins/ExtendedVeinsInetMobility.h"

using namespace std;

Define_Module(GlobalPlatoonsManager);



PlatoonController* GlobalPlatoonsManager::createNewPlatoon(){
    string platoonId = nextPlatoonId();
    string platoonModuleName = PLATOON_MODULE_BASE_NAME+platoonId;
    cModule *mod = cModuleType::get("simulator_5g_v2x.modules.Platoon")->createScheduleInit(platoonModuleName.c_str(), findModuleByPath("<root>"));
    PlatoonController* cont = check_and_cast<PlatoonController *>(mod->getSubmodule("platoonController"));
    platoons.insert(pair<string, PlatoonController*>(platoonId, cont));
    return cont;
}


bool GlobalPlatoonsManager::vehiclePlatoonLogicRegistration(status_t status){
    Enter_Method("vehiclePlatoonLogicRegistration");

    // Vehicle could be already present. If so simply return true
    if (physicalMap.count(status.sumoCarId) > 0){
        EV_WARN << status.sumoCarId << " has already performed the logic registration" << endl;
        return true;
    }

    EV_INFO << status.sumoCarId << " is asking for logic registration, front vehicle: "<< status.frontVehicle << endl;
//    cout <<simTime()<< " "<< status.sumoCarId << " is asking for logic registration, front vehicle: "<< status.frontVehicle << endl;

    PlatoonController *platoonCtl = nullptr;
    //Case 1: leader
    if (status.sumoCarId.compare("leader") == 0){
        platoonCtl = createNewPlatoon();
        EV_INFO << "Created new platoon "<< platoonCtl->getPlatoonId() <<endl;
    }
    // Case 2: follower
    else if (physicalMap.count(status.frontVehicle) > 0) {  //Front vehicle should have been already added
        platoonCtl = platoons.at(physicalMap[status.frontVehicle].platoonId);
    }
    else{ //error
        cout << simTime() <<" Front vehicle is not registered. This should not happen " << status.sumoCarId << " --> "<< status.frontVehicle << endl;
        throw new cRuntimeError("Front vehicle is not registered. This should not happen");
    }

    // add vehicle to the right platoon
    string platoonCarId = platoonCtl->addVehicleBack(status);
    PhyPlatoonMemberInfo_t info = {platoonCtl->getPlatoonId(), platoonCarId, status.carId};
    physicalMap.insert(pair<string, PhyPlatoonMemberInfo_t>(status.sumoCarId, info));

    return true;
}


platoon_car_info_t GlobalPlatoonsManager::completeRegistration(string physicalId){
    Enter_Method("completeRegistration");
    if(physicalMap.count(physicalId) == 0){
        EV_ERROR<< physicalId << " should have been registered! Check your code!"<< endl;
        throw new cRuntimeError("completeRegistration: Platoon vehicle not found!");
    }
    // Update registration status to "completed"
    physicalMap[physicalId].networkRegistered = true;

    auto info = physicalMap[physicalId];

    platoon_car_info_t platoonCarInfo;
    platoonCarInfo.platoonId = info.platoonId;
    platoonCarInfo.platoonCarId = info.platoonCarId;
    platoonCarInfo.position =  platoons.at(info.platoonId)->getPositionByCarId(info.platoonCarId);

    return platoonCarInfo;
}


//string GlobalPlatoonsManager::addVehicle(string platoonId, string carId, string physicalId, double vehicleLength,
//        int position, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt){
//    EV << "CREAZIONE " << dataCreatedAt << endl;
//    if(physicalMap.count(physicalId) > 0){		//Check if physId already exists
//        //return physicalMap.at(physicalId).second;
//        return "";
//    }else{
//        string platoonCarId = platoons.at(platoonId)->addVehicle(vehicleLength, position, speed, acceleration, distance, sequenceNumber, dataCreatedAt);
//        PhyPlatoonMemberInfo_t info {platoonId, platoonCarId, carId};
//        physicalMap.insert(pair<string, PhyPlatoonMemberInfo_t>(physicalId, info));
//
//        return platoonCarId;
//    }
//}


vehicle_t GlobalPlatoonsManager::getVehicleByPosition(string platoonId, int i){
    return platoons.at(platoonId)->getVehicleByPosition(i);
}

void GlobalPlatoonsManager::removeVehicle(string platoonId, string carId) {
    platoons.at(platoonId)->removeVehicle(carId);
}

list<pair<string, double>> GlobalPlatoonsManager::updateAndCompute(string platoonId, string platoonCarId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt) {
    Enter_Method("GlobalPlatoonsManager::updateAndCompute");
    return platoons.at(platoonId)->updateAndCompute(platoonCarId, speed, acceleration, distance, sequenceNumber, dataCreatedAt);
}

bool GlobalPlatoonsManager::isLastVehicle(string platoonId, string carId){
//    for (auto const &p : platoons){
//        cout << p.first << " == " << platoonId.size() << endl;
//    }

    return platoons.at(platoonId)->isLastVehicle(carId);
}


bool GlobalPlatoonsManager::isPlatoonLeader(string platoonId, string carId){
    return platoons.at(platoonId)->isLeaderVehicle(carId);
}

int GlobalPlatoonsManager::platoonSize(string platoonId){
    return platoons.at(platoonId)->size();
}

int GlobalPlatoonsManager::platoonSizeFromPhysicalVehicleId(string physicalId){
    if (physicalMap.count(physicalId) == 0)
        return -1;
    return platoons.at(physicalMap.at(physicalId).platoonId)->size();
}

int GlobalPlatoonsManager::getPositionByPhysicalVehicleId(string physicalId){
    if (physicalMap.count(physicalId) == 0)
        return -1;

    auto platoonCarId = physicalMap.at(physicalId).platoonCarId;
    return platoons.at(physicalMap.at(physicalId).platoonId)->getPositionByCarId(platoonCarId);
}

bool GlobalPlatoonsManager::hasVehicleByPhysicalVehicleId(string physicalId){
    return !(physicalMap.count(physicalId) == 0);
}

PhyPlatoonMemberInfo_t GlobalPlatoonsManager::getVehicleInfoByPhysicalVehicleId(string physicalId){
    return physicalMap.at(physicalId); //exception if not found
}

/*
void GlobalPlatoonsManager::computeCACCControlLaw(){
    for (std::map<string, PlatoonController*>::iterator it = platoons.begin(); it != platoons.end(); ++it) {
            it->second->computeCACCControlLaw();
        }
}*/


PhyPlatoonMemberInfo_t GlobalPlatoonsManager::getVehicleInfoByPositon(string platoonId, int pos){
    string platoonCarId = platoons.at(platoonId)->getVehicleByPosition(pos).platoonCarId;

    for (auto const &p : physicalMap){
        if (p.second.platoonCarId.compare(platoonCarId) == 0){
            return p.second;
        }
    }

    throw runtime_error("GlobalPlatoonsManager::getVehicleInfoByPositon: Not found!");
}


string GlobalPlatoonsManager::nextPlatoonId(){
    return to_string(nextPlatoonNumber++);
}
