#ifndef MODULES_GLOBALPLATOONSMANAGER_H_
#define MODULES_GLOBALPLATOONSMANAGER_H_

#include <string>
#include <list>
#include <algorithm>
#include <omnetpp.h>

#include "common/types_t.h"
#include "common/constants.h"
#include "modules/platooncontroller/PlatoonController.h"


using namespace omnetpp;
using namespace std;

typedef struct {
    string platoonId;
    string platoonCarId;
    string carId;
    bool networkRegistered = false;  //if false it means that packet has not arrived yet. Only logical registration has been done!
} PhyPlatoonMemberInfo_t;


typedef struct {
    string platoonId;
    string platoonCarId;
    int position;
} platoon_car_info_t;


class GlobalPlatoonsManager : public cSimpleModule{

public:
    /**
     * Direct vehicle registration.
     * ASSUMPTIONS:
     * - Vehicles of the platoon are created sequentially
     * - All vehicles travel on the same lane
     * - SUMO name of the platoon leader MUST BE "leader"
     */
    bool vehiclePlatoonLogicRegistration(status_t status);

    /*
     * This should be called by MEC service to complete the registration.
     * This means that the packet has reached the MEC service.
     */
    platoon_car_info_t completeRegistration(string physicalId);


//    pair<string,int> getBestPlatoon(string physicalId, string precedingCarId);

    vehicle_t getVehicleByPosition(string platoonId, int i);
    void removeVehicle(string platoonId, string carId);
    list<pair<string, double>> updateAndCompute(string platoonId, string platoonCarId, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt);
    bool isLastVehicle(string platoonId, string carId);
    bool isPlatoonLeader(string platoonId, string carId);
    int platoonSize(string platoonId);
    int platoonSizeFromPhysicalVehicleId(string physicalId);
    int getPositionByPhysicalVehicleId(string physicalId);
    string getPlatoonByPhysicalVehicleId(string physicalId);
    PhyPlatoonMemberInfo_t getVehicleInfoByPhysicalVehicleId(string physicalId);
    PhyPlatoonMemberInfo_t getVehicleInfoByPositon(string platoonId, int pos);
    bool hasVehicleByPhysicalVehicleId(string physicalId);
    //void computeCACCControlLaw();



private:
    int nextPlatoonNumber = 0;
    string nextPlatoonId();

    map<string, PlatoonController*> platoons;
    map<string, PhyPlatoonMemberInfo_t> physicalMap;


    PlatoonController* createNewPlatoon();

//    string addVehicle(string platoonId, string physicalId, string carId, double vehicleLength, int position, double speed, double acceleration, double distance, int sequenceNumber, double dataCreatedAt);


};

#endif /* MODULES_GLOBALPLATOONSMANAGER_H_ */
