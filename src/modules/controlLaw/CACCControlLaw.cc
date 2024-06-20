#include "CACCControlLaw.h"
#include "modules/extendedveins/ExtendedVeinsInetMobility.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"

Define_Module(CACCControlLaw);

CACCControlLaw::CACCControlLaw() {}

CACCControlLaw::~CACCControlLaw() {}

list<double> CACCControlLaw::computeLaw(list<string> toUpdate) {
    EV << "CACCControlLaw::computeLaw" << endl;
    list<double> newAcc = list<double>();
    for (list<string>::iterator it = toUpdate.begin(); it != toUpdate.end(); ++it) {
        newAcc.push_back(computePerVehicle(*it));
    }
    return newAcc;
}

double CACCControlLaw::computeLaw(string vehicleId){
    return computePerVehicle(vehicleId);
}


double CACCControlLaw::computeLawUsingSensorData(string physicalCarId){
    auto gpm = check_and_cast<GlobalPlatoonsManager*>(findModuleByPath("<root>.globalPlatoonsManager"));

    auto vehicleInfo = gpm->getVehicleInfoByPhysicalVehicleId(physicalCarId);

    int i = gpm->getPositionByPhysicalVehicleId(physicalCarId);
    if (i == 0)
        return 0.0;


    string carId = vehicleInfo.carId;
    string frontCarId = gpm->getVehicleInfoByPositon(vehicleInfo.platoonId, i-1).carId;
    string leaderCarId = gpm->getVehicleInfoByPositon(vehicleInfo.platoonId, 0).carId;

    auto thisVehicleCmdInteface = veins::VeinsInetMobilityAccess().get(getModuleByPath(("<root>."+ carId).c_str()))->getVehicleCommandInterface();
    auto frontVehicleCmdInteface = veins::VeinsInetMobilityAccess().get(getModuleByPath(("<root>."+frontCarId).c_str()))->getVehicleCommandInterface();
    auto leaderVehicleCmdInteface = veins::VeinsInetMobilityAccess().get(getModuleByPath(("<root>."+leaderCarId).c_str()))->getVehicleCommandInterface();

    vehicle_t car_i;
    car_i.acceleration = thisVehicleCmdInteface->getAcceleration();
    car_i.speed = thisVehicleCmdInteface->getSpeed();
    car_i.distance = thisVehicleCmdInteface->getLeader(10000).second;

    vehicle_t carFront;
    carFront.acceleration =frontVehicleCmdInteface->getAcceleration();
    carFront.speed = frontVehicleCmdInteface->getSpeed();

    vehicle_t carLeader;
    carLeader.acceleration =  leaderVehicleCmdInteface->getAcceleration();
    carLeader.speed = leaderVehicleCmdInteface->getSpeed();

    return computeCACCControlLaw(car_i, carFront, carLeader);

}

void CACCControlLaw::initialize() {
    EV << "CACCControlLaw::initialize" << endl;
    c1 = par("C1");
    csi = par("csi");
    omega_n = par("omega_n");
    targetDistance = par("distance");

    alpha1 = 1 - c1;
    alpha2 = c1;
    alpha3 = -(2 * csi - c1 * (csi + sqrt(pow(csi, 2) - 1))) * omega_n;
    alpha4 = (-c1) * (csi + sqrt(pow(csi, 2) - 1)) * omega_n;
    alpha5 = -pow(omega_n, 2);

    cModule* platoonController = getParentModule()->getSubmodule("platoonController");
    if (platoonController)
        vehiclesDataProvider=
                (VehiclesDataProvider*)check_and_cast<PlatoonController*>(platoonController);
}

double CACCControlLaw::computePerVehicle(string platoonCarId) {
    Enter_Method("computePerVehicle");
    EV << "CACCControlLaw::computePerVehicle --- computing carId: " << platoonCarId << endl;
    int i = vehiclesDataProvider->getPositionByCarId(platoonCarId);

    vehicle_t car_i = vehiclesDataProvider->getVehicleByPosition(i);
    vehicle_t car_i_1 = vehiclesDataProvider->getVehicleByPosition(i - 1);
    vehicle_t car_0 = vehiclesDataProvider->getVehicleByPosition(0);

    double acc_des_i = computeCACCControlLaw(car_i, car_i_1, car_0);

    EV << "CACCControlLaw::computePerVehicle --- carId: " << platoonCarId << " computed: " << acc_des_i << endl;
    return acc_des_i;
}

double CACCControlLaw::getTargetDistance(vehicle_t data){
    return 0.0;
}

double CACCControlLaw::getTargetDistance(status_t data){
    return 0.0;
}

double CACCControlLaw::computeCACCControlLaw(vehicle_t v, vehicle_t front, vehicle_t leader){
    double ei_d = v.speed - front.speed;
    double ei = (-v.distance) + targetDistance;
    double acc_des = alpha1 * front.acceleration + alpha2 * leader.acceleration + alpha3 * ei_d +
            alpha4 * (v.speed - leader.speed) + alpha5 * ei;

    return acc_des;
}



list<int> CACCControlLaw::getUsedPlatoonVehiclePositions(string platoonCarId){
    int i = vehiclesDataProvider->getPositionByCarId(platoonCarId);
    return {0, i-1, i};

}
