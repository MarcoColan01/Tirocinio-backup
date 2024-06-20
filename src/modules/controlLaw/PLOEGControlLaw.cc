#include "PLOEGControlLaw.h"
#include "modules/extendedveins/ExtendedVeinsInetMobility.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"

Define_Module(PLOEGControlLaw);

PLOEGControlLaw::PLOEGControlLaw() {}

PLOEGControlLaw::~PLOEGControlLaw() {}

list<double> PLOEGControlLaw::computeLaw(list<string> toUpdate) {
    EV << "PLOEGControlLaw::computeLaw" << endl;
    list<double> newAcc = list<double>();
    for (list<string>::iterator it = toUpdate.begin(); it != toUpdate.end(); ++it) {
        newAcc.push_back(computePerVehicle(*it));
    }
    return newAcc;
}

double PLOEGControlLaw::computeLaw(string vehicleId){
    return computePerVehicle(vehicleId);
}


//A ME QUESTA NON SERVE!!!!
double PLOEGControlLaw::computeLawUsingSensorData(string physicalCarId){
    auto gpm = check_and_cast<GlobalPlatoonsManager*>(findModuleByPath("<root>.globalPlatoonsManager"));

    auto vehicleInfo = gpm->getVehicleInfoByPhysicalVehicleId(physicalCarId);

    int i = gpm->getPositionByPhysicalVehicleId(physicalCarId);
    if (i == 0)
        return 0.0;


    string carId = vehicleInfo.carId;
    string frontCarId = gpm->getVehicleInfoByPositon(vehicleInfo.platoonId, i-1).carId;

    auto thisVehicleCmdInteface = veins::VeinsInetMobilityAccess().get(getModuleByPath(("<root>."+ carId).c_str()))->getVehicleCommandInterface();
    auto frontVehicleCmdInteface = veins::VeinsInetMobilityAccess().get(getModuleByPath(("<root>."+frontCarId).c_str()))->getVehicleCommandInterface();

    vehicle_t car_i;
    car_i.acceleration = thisVehicleCmdInteface->getAcceleration();
    car_i.speed = thisVehicleCmdInteface->getSpeed();
    car_i.distance = thisVehicleCmdInteface->getLeader(10000).second;

    vehicle_t carFront;
    carFront.acceleration =frontVehicleCmdInteface->getAcceleration();
    carFront.speed = frontVehicleCmdInteface->getSpeed();
    //carFront.distance = frontVehicleCmdInteface->getLeader(10000).second;


    return computePLOEGControlLaw(car_i, carFront);

}

void PLOEGControlLaw::initialize() {
    EV << "PLOEGControlLaw::initialize" << endl;
    k_p = par("k_p");
    headwayDistance = par("h");
    k_d = par("k_d");

    cModule* platoonController = getParentModule()->getSubmodule("platoonController");
    if (platoonController)
        vehiclesDataProvider=
                (VehiclesDataProvider*)check_and_cast<PlatoonController*>(platoonController);
}

double PLOEGControlLaw::computePerVehicle(string platoonCarId) {
    Enter_Method("computePerVehicle");
    EV << "PLOEGControlLaw::computePerVehicle --- computing carId: " << platoonCarId << endl;
    int i = vehiclesDataProvider->getPositionByCarId(platoonCarId);

    vehicle_t car_i = vehiclesDataProvider->getVehicleByPosition(i);
    vehicle_t car_i_1 = vehiclesDataProvider->getVehicleByPosition(i - 1);

    double acc_des_i = computePLOEGControlLaw(car_i, car_i_1);

    EV << "PLOEGControlLaw::computePerVehicle --- carId: " << platoonCarId << " computed: " << acc_des_i << endl;
    return acc_des_i;
}


double PLOEGControlLaw::computePLOEGControlLaw(vehicle_t v, vehicle_t front){
    std::cout << "Front vehicle desired acceleration: " << front.desiredAcceleration << std::endl;
    std::cout << "This vehicle desired acceleration: " << v.desiredAcceleration << std::endl;
    return (1/headwayDistance)*(-v.desiredAcceleration + k_p*(v.distance-getTargetDistance(v))
            +k_d*(front.speed-v.speed-(headwayDistance*v.acceleration))+ front.desiredAcceleration);
}

double PLOEGControlLaw::getTargetDistance(vehicle_t data){
    return data.speed*headwayDistance;
}

double PLOEGControlLaw::getTargetDistance(status_t data){
    return data.speed*headwayDistance;
}




list<int> PLOEGControlLaw::getUsedPlatoonVehiclePositions(string platoonCarId){
    int i = vehiclesDataProvider->getPositionByCarId(platoonCarId);
    return {i-1, i};


}
