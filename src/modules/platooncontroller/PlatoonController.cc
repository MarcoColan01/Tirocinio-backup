#include "PlatoonController.h"

Define_Module(PlatoonController);


string PlatoonController::addVehicleBack(status_t status) {
    string newId = to_string(getNextCarId());
    EV << "PlatoonController::addVehicle --- Adding vehicle with carId: " << newId << endl;
    vehicle_t newCar = {newId, status.vehicleLength,

            status.speed, status.acceleration,
            status.distance, status.desiredAcceleration};

    cars.push_back(newCar);     //Add vehicle at the end

    graph->addVehicle(newId);
    return newId;
}




string PlatoonController::addVehicle(double vehicleLength, int position, double speed, double acceleration, double distance, double desiredAcc, int sequenceNumber, double dataCreatedAt) {
    string newId = to_string(getNextCarId());
    EV << "PlatoonController::addVehicle --- Adding vehicle with carId: " << newId << endl;
    vehicle_t newCar = {newId, vehicleLength, speed, acceleration, distance, desiredAcc, sequenceNumber, dataCreatedAt};
    if(position < 0)
        cars.push_back(newCar);     //Add vehicle at the end
    else
        cars.insert(cars.begin()+position, newCar);

    graph->addVehicle(newId);
    return newId;
}


int PlatoonController::getPositionByCarId(string platoonCarId) {
    for(size_t i = 0; i < cars.size(); i++)
        if(!strcmp(cars[i].platoonCarId.c_str(), platoonCarId.c_str()))
            return i;

    return -1;
}

string PlatoonController::getCarIdByPosition(int position) {
    EV << "PlatoonController::getCarByIdPosition" << endl;
    return cars.at(position).platoonCarId;
}

bool PlatoonController::exists(int position){
    return position >= 0 && position < cars.size();
}

void PlatoonController::updateStatus(string carId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt) {
    Enter_Method("updateStatus");
    int i = getPositionByCarId(carId);
    cars[i].speed = speed;
    cars[i].acceleration = acceleration;
    cars[i].distance = distance;
    cars[i].sequenceNumber = sequenceNumber;
    cars[i].creationTime = dataCreatedAt;
    cars[i].networkRegistered = true;
}

list<string> PlatoonController::checkAndFilterRegistered(list<string> &carList){
    list<string> filteredList;
    for (auto platoonCarId : carList){
        bool valid = true;
        for (auto i : law->getUsedPlatoonVehiclePositions(platoonCarId)){
            valid &=getVehicleByPosition(i).networkRegistered;
        }
        if (valid){
            filteredList.push_back(platoonCarId);
        }
    }
    return filteredList;
}

list<pair<string, double>> PlatoonController::updateAndCompute(string platoonCarId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt) {
    EV << "PlatoonController::updateAndCompute --- For carId: " << platoonCarId << endl;
    updateStatus(platoonCarId, speed, acceleration, distance, sequenceNumber, dataCreatedAt);
    list<string> carsToUpdate = graph->getVehicleDependencies(platoonCarId);
    carsToUpdate = checkAndFilterRegistered(carsToUpdate);
    list<double> newAccs =  law->computeLaw(carsToUpdate);
    if(carsToUpdate.size() != newAccs.size())
        throw cRuntimeError("Dependencies and accelerations lists have different size");

    list<pair<string, double>> toRet;
    list<double>::iterator accIt = newAccs.begin();
    for(list<string>::iterator it = carsToUpdate.begin(); it != carsToUpdate.end(); it++){
        toRet.push_back(pair<string, double>(*it, *accIt));
        accIt++;
    }
    return toRet;
}

string PlatoonController::getPlatoonIdFromParent(){
    string parentModuleName = getParentModule()->getFullName();
    return parentModuleName.substr(strlen(PLATOON_MODULE_BASE_NAME));
}



void PlatoonController::initialize(){
    EV << "PlatoonController::initialize" << endl;
    nextCarId = 0;
    graph = check_and_cast<DependencyGraph *>(getParentModule()->getSubmodule("dependencyGraph"));
    law = check_and_cast<ControlLaw *>(getParentModule()->getSubmodule("controlLaw"));
    platoonId = getPlatoonIdFromParent();
}

vehicle_t PlatoonController::getVehicleByPosition(int position) {
    return cars.at(position);
}

void PlatoonController::removeVehicle(string carId) {
}

//Sequential assignment (id free not managed)
uint16_t PlatoonController::getNextCarId(){
    return nextCarId++;
}

bool PlatoonController::isLastVehicle(string platoonCarId){
    return cars.back().platoonCarId.compare(platoonCarId) == 0;
}

bool PlatoonController::isLeaderVehicle(string platoonCarId){
    return cars.front().platoonCarId.compare(platoonCarId) == 0;
}

int PlatoonController::size(){
    return cars.size();
}

/*
void PlatoonController::computeCACCControlLaw(){

    for(int i = cars.size()-1; i >0 ;i--){
        c1 = par("C1");
        csi = par("csi");
        omega_n = par("omega_n");
        targetDistance = par("distance");

        alpha1 = 1 - c1;
        alpha2 = c1;
        alpha3 = -(2 * csi - c1 * (csi + sqrt(pow(csi, 2) - 1))) * omega_n;
        alpha4 = (-c1) * (csi + sqrt(pow(csi, 2) - 1)) * omega_n;
        alpha5 = -pow(omega_n, 2);
        double ei_d = cars[i].speed - cars[i-1].speed;
        double ei = (-cars[i].distance) + targetDistance;
        double acc_des = alpha1 * cars[i-1].acceleration + alpha2 * cars[0].acceleration + alpha3 * ei_d +
                        alpha4 * (cars[i].speed - cars[0].speed) + alpha5 * ei;
        cars[i].controlLaw = acc_des;
    }
}
*/
