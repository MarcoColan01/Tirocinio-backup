#ifndef SELFVEHICLEPOSITIONPROVIDER_H
#define SELFVEHICLEPOSITIONPROVIDER_H

#include <omnetpp.h>

#include "modules/controlLaw/VehiclesDataProvider.h"

using namespace std;
class SelfVehiclesDataProvider : public VehiclesDataProvider {
  map<int, vehicle_t> carsData;

 public:
  void addVehicle(vehicle_t carData) { carsData[stoi(carData.platoonCarId)] = carData; }
  vehicle_t getVehicleByPosition(int position) override { return carsData[position]; };
  int getPositionByCarId(string carId) override { return stoi(carId); };
  bool exists(int position) { return carsData.find(position) != carsData.end(); }
  void remove(string carId){
    carsData.erase(stoi(carId));
  }

  double getAoIVehicleData(int carId, double simtime){
//      cout << carId << " " << carsData[carId].creationTime << endl;
      return simtime - carsData[carId].creationTime;
  }

  void print(){
    for(auto& x : carsData){
      EV << x.first << " ";
    }
    EV << endl;
  }
};

#endif
