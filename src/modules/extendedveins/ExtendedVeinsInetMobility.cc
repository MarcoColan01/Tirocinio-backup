

#include "modules/extendedveins/ExtendedVeinsInetMobility.h"

#include <omnetpp.h>

namespace veins {

Define_Module(ExtendedVeinsInetMobility)

        std::pair<std::string, double> ExtendedVehicle::getFollower(
                const double distance) {
    const uint8_t VAR_FOLLOWER = 0x78;
    TraCIBuffer request = TraCIBuffer()
                                << VAR_FOLLOWER << nodeId << TYPE_DOUBLE << distance;
    TraCIBuffer response = connection->query(CMD_GET_VEHICLE_VARIABLE, request);

    uint8_t cmdLength;
    response >> cmdLength;
    if (cmdLength == 0) {
        uint32_t cmdLengthX;
        response >> cmdLengthX;
    }
    uint8_t responseId;
    response >> responseId;
    ASSERT(responseId == RESPONSE_GET_VEHICLE_VARIABLE);
    uint8_t variableType;
    response >> variableType;
    ASSERT(variableType == VAR_FOLLOWER);
    std::string rspNodeId;
    response >> rspNodeId;
    ASSERT(strcmp(rspNodeId.c_str(), nodeId.c_str()) == 0);
    uint8_t responseType;
    response >> responseType;
    ASSERT(responseType == TYPE_COMPOUND);
    uint32_t numElements;
    response >> numElements;
    ASSERT(numElements == 2);
    uint8_t leaderType;
    response >> leaderType;
    ASSERT(leaderType == TYPE_STRING);
    std::string followerId;
    response >> followerId;
    uint8_t distanceType;
    response >> distanceType;
    ASSERT(distanceType == TYPE_DOUBLE);
    double distanceToFollower;
    response >> distanceToFollower;

    ASSERT(response.eof());

    return std::make_pair(followerId, distanceToFollower);
}

bool ExtendedVehicle::checkCollision(){
    //const uint8_t VAR = 0x78;
    std::string simId = "sim0";
    TraCIBuffer request = TraCIBuffer() << VAR_COLLIDING_VEHICLES_NUMBER << simId;
    TraCIBuffer response = connection->query(CMD_GET_SIM_VARIABLE, request);
    uint8_t cmdLength;
    response >> cmdLength;
    if (cmdLength == 0) {
        uint32_t cmdLengthX;
        response >> cmdLengthX;
    }
    uint8_t responseId;
    response >> responseId;
    ASSERT(responseId == RESPONSE_GET_SIM_VARIABLE);
    uint8_t variable;
    response >> variable;
    ASSERT(variable == VAR_COLLIDING_VEHICLES_NUMBER); // Check if the response is what I asked
    std::string id;
    response >> id;
    uint8_t varType;
    response >> varType;
    ASSERT(varType == TYPE_INTEGER);
    uint32_t count;
    response >> count;

    return count > 0;
}

void ExtendedVehicle::setLaneChangeMode(int32_t bitset){
    uint8_t variableId = 0xb6;
    uint8_t variableType = TYPE_INTEGER;
    TraCIBuffer buf = connection->query(CMD_SET_VEHICLE_VARIABLE, TraCIBuffer() << variableId << nodeId << variableType << bitset);
    ASSERT(buf.eof());
}

void ExtendedVehicle::setMinGap(double minGap){
    uint8_t variableId = 0x4c;
    uint8_t variableType = TYPE_DOUBLE;
    TraCIBuffer buf = connection->query(CMD_SET_VEHICLE_VARIABLE, TraCIBuffer() << variableId << nodeId << variableType << minGap);
    ASSERT(buf.eof());
}


void ExtendedVehicle::setAcceleration(double acc, double t){
    uint8_t variableId = VAR_ACCELERATION;
    uint8_t variableType = TYPE_COMPOUND;
    int32_t count = 2;
    uint8_t accT = TYPE_DOUBLE;
    uint8_t timeT = TYPE_DOUBLE;
    TraCIBuffer buf = connection->query(CMD_SET_VEHICLE_VARIABLE, TraCIBuffer() << variableId << nodeId << variableType << count << accT << acc << timeT << t);
    ASSERT(buf.eof());
}


TraCICommandInterface::Vehicle*
ExtendedVeinsInetMobility::getVehicleCommandInterface() const {
    if (!vehicleCommandInterface)
        vehicleCommandInterface =
                new ExtendedVehicle(getCommandInterface()->vehicle(getExternalId()));
    return vehicleCommandInterface;
}

}  // namespace veins
