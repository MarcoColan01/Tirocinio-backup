#ifndef TYPES_T
#define TYPES_T

#include <omnetpp.h>
using namespace std;

typedef struct {
    string platoonCarId;
    double vehicleLength;
    double speed;
    double acceleration;
    double distance;
    double desiredAcceleration;
    int sequenceNumber = - 1;  // <0 means no packet has received yet
    double creationTime = - 1.0;  // <0 means no packet has received yet
    bool networkRegistered = false;
    //double controlLaw;
}vehicle_t;



typedef struct {
    std::string sumoCarId;
    std::string carId;
    double vehicleLength;
    double speed;
    double acceleration;
    double distance = -1;
    std::string frontVehicle;
    std::string behindVehicle;
    double behindDistance = -1;
    double position_x;
    double position_y;
    double position_z;
    double desiredAcceleration;
} status_t;


#endif
