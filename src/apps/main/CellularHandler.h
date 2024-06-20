#ifndef APPS_MAIN_CELLULARHANDLER_H_
#define APPS_MAIN_CELLULARHANDLER_H_

#include "common/types_t.h"
#include "modules/decider/BaseDecider.h"
#include "Handler.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"

using namespace std;
using namespace inet;

class CellularHandler : public Handler, UdpSocket::ICallback {
    SocketWrapper *socket;
    bool platoonRegistered = false;
    void createAndSendPlatoonRegisterPacket(status_t status);
    void createAndSendStatusPacket(status_t status);
    cModule* parent;
    BaseDecider* decider;
    int sequenceNumber = 1;
    //mappa (sequence number, tempo di emissione)
    map<int,double> sequenceTime;

    simsignal_t mecDelaySignal;

public:
    CellularHandler(cModule* p){
        parent = p;
        mecDelaySignal = parent->registerSignal("mecDelay");
        decider = check_and_cast<BaseDecider*>(p->getParentModule()->getSubmodule("decider"));
    }


    virtual const char *getName() override { return "CellularHandler"; }
    virtual void init(map<int, SocketWrapper *>) override;
    virtual bool isReady() override;
    virtual void onNewDataArrived(status_t p) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;

    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override {}
    virtual void socketClosed(UdpSocket *socket) override {}

    virtual void updateInstructionManager(InstructionManager* instructionMng, double instruction) override{
        instructionMng->setCellularInstruction(instruction);
    }

private:
//    // Thrown an exception if vehicle has not been correctly registered
//    void vehiclePlatoonLogicRegistration(status_t status);
};

#endif /* APPS_MAIN_CELLULARHANDLER_H_ */
