#ifndef __VIRTUALVEHICLEMECAPP_H_
#define __VIRTUALVEHICLEMECAPP_H_


#include "omnetpp.h"

#include <string>
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

#include "apps/mec/MecApps/MecAppBase.h"


#include "apps/packets/VehicleControlPacket_m.h"
#include "apps/packets/VehicleControlPacket_Types.h"


using namespace std;
using namespace omnetpp;
using namespace inet;

class VirtualVehicleMECApp : public MecAppBase
{
private:
    //UDP socket to communicate with the UeApp
    inet::UdpSocket ueSocket;
    int localUePort;

    inet::L3Address ueAppAddress;
    int ueAppPort;

    inet::TcpSocket* serviceSocket_;
    inet::TcpSocket* mp1Socket_;

    HttpBaseMessage* mp1HttpMessage;
//    HttpBaseMessage* serviceHttpMessage;


    string platoonId;
    string carId;
    string physicalId;
    string platoonCarId;
    bool isLeader;
    double thisAoi;
    double precedingAoi;
    double leaderAoi;

    double vehicleLength;
    double speed;
    double acceleration;            //Read from vehicle
    double desiredAcc;
    double distance;
    double creationTime = 0;
    int sequenceNumber;
    string frontVehicle;
    double posX, posY, posZ;
    simtime_t minStatusDistance;
    simtime_t lastStatusReceived;
    simtime_t lastStatusArrival;

    double instructionAcceleration; //To be sent to vehicle
    string instructionTriggeringCarId;

    cMessage *sendStartAckPacket_;
    double startAckTimeout_;

    double packetDropRate_;

    simsignal_t statusAgeOfInfoSignal;
    simsignal_t statusDiscardedSignal;

    simsignal_t vehicleStatusPacketDelay;


    void sendPlatoonInfoToUe();

    void initializeVirtualVehicleStatus(Packet *pkt);
    /**
     * Update virtual status managing the timestamp of the message
     * @return true if status has been update, false otherwise
     */
    bool updateVirtualVehicleStatus(Packet *pkt);


protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
//    virtual void handleMessage(cMessage *msg) override;

    virtual void finish() override;

    virtual void handleProcessedMessage(omnetpp::cMessage *msg);
    virtual void handleUeMessage(omnetpp::cMessage *msg) override;
    virtual void handleServiceMessage(int connId) override;
    virtual void handleMp1Message(int connId) override;
    virtual void handleHttpMessage(int connId) override;



    //Ue messages

    virtual void sendInstructionMessage();
    virtual void sendStartAckPacket();
    virtual void handleSelfMessage(cMessage *msg) override;


    //        /* TCPSocket::CallbackInterface callback methods */
    virtual void established(int connId) override;
    //        virtual void socketDataArrived(inet::TcpSocket *socket, inet::Packet *msg, bool urgent) override;
    //
    //        virtual void socketDataArrived(inet::UdpSocket *socket, inet::Packet *packet) override;
    //        virtual void socketErrorArrived(inet::UdpSocket *socket, inet::Indication *indication) override;
    //        virtual void socketClosed(inet::UdpSocket *socket) override {};


    //Service methods
    virtual void sendPUT();
    virtual void sendPOST();

public:
    VirtualVehicleMECApp();
    virtual ~VirtualVehicleMECApp();

};

#endif
