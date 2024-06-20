#ifndef __SIMULATOR_5G_V2X_PLATOONCONTROLLER_H_
#define __SIMULATOR_5G_V2X_PLATOONCONTROLLER_H_

#include <omnetpp.h>

#include "common/types_t.h"
#include "common/constants.h"
#include "modules/dependencyGraph/DependencyGraph.h"
#include "modules/controlLaw/ControlLaw.h"
#include "modules/controlLaw/VehiclesDataProvider.h"
using namespace omnetpp;
using namespace std;

class PlatoonController : public cSimpleModule, VehiclesDataProvider
{
public:
    string addVehicleBack(status_t status);
    string addVehicle(double vehicleLength, int position, double speed, double acceleration, double distance,double desiredAcc, int sequenceNumber, double dataCreatedAt);
    void updateStatus(string carId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt);
    void removeVehicle(string carId);
    list<pair<string, double>> updateAndCompute(string platoonCarId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt);
    int getPositionByCarId(string carId) override;
    string getCarIdByPosition(int position);
    vehicle_t getVehicleByPosition(int position) override;
    bool exists(int position) override;
    bool isLastVehicle(string platoonCarId);
    bool isLeaderVehicle(string platoonCarId);
    int size();
    string getPlatoonId(){return platoonId;}
    //void computeCACCControlLaw();
protected:
    virtual void initialize() override;
    uint16_t getNextCarId();
private:
    vector<vehicle_t> cars;
    uint16_t nextCarId;
    DependencyGraph *graph;
    ControlLaw *law;
    string platoonId;  //get from the parent name module during initialization

    string getPlatoonIdFromParent();
    list<string> checkAndFilterRegistered(list<string> &carList);
    /*double c1, csi, omega_n, targetDistance;
    double alpha1, alpha2, alpha3, alpha4, alpha5;*/
};

#endif
