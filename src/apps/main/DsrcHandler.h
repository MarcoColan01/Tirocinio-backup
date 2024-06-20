/*
 * OfflineHandler.h
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#ifndef APPS_MAIN_DSRCHANDLER_H_
#define APPS_MAIN_DSRCHANDLER_H_

#include <omnetpp.h>

#include "Handler.h"
#include "SelfVehiclesDataProvider.h"
#include "inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211Radio.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "modules/controlLaw/CACCControlLaw.h"
#include "modules/controlLaw/PLOEGControlLaw.h"
#include "modules/powercontroller/PowerController.h"
#include "modules/decider/BaseDecider.h"


using namespace std;
using namespace inet;
using namespace physicallayer;


class DsrcHandler : public Handler, UdpSocket::ICallback {
public:

    DsrcHandler(const char *platoonId, const char *platoonCarId, cModule *parent,
            ControlLaw *ControlLaw, PowerController *powerController, OnboardControlLawMode controlLawMode);

    virtual void init(map<int, SocketWrapper *>) override;
    virtual bool isReady() override;
    virtual void onNewDataArrived(status_t p) override;

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;

    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override {}
    virtual void socketClosed(UdpSocket *socket) override {}

    virtual const char *getName() override { return "DsrcHandler"; }


    virtual void updateInstructionManager(InstructionManager* instructionMng, double instruction) override {
        instructionMng->setDsrcInstruction(instruction);
    }


private:
    SocketWrapper *socket;
    SelfVehiclesDataProvider *vehiclesDataProvider;
    ControlLaw *controlLaw;
    OnboardControlLawMode controlLawMode;
    string platoonId;
    string platoonCarId;
    bool isLastVehicleInPlatoon;
    int platoonSize;
    PowerController *powerController;
    cModule *parent;
    bool nextMaxPower;

    BaseDecider* decider;


    void sendStatusUpdate(status_t status);
    void computeControlLaw();

    /**
     * Check if all required data for computing the control law are available
     */
    bool hasAllRequiredVehicleData(){
        return vehiclesDataProvider->exists(stoi(platoonCarId) - 1) &&
                vehiclesDataProvider->exists(0);
    }

    bool dependOnVehicle(string carId){
        int carId_i = stoi(carId);
        return (carId_i - 1) == stoi(platoonCarId) || carId_i == 0;  //Preceding or leader
    }


    bool isLeader(){
        return strcmp(platoonCarId.c_str(), "0") == 0;
    }

    bool isFollower(){
        return !isLeader();
    }

};

#endif /* APPS_MAIN_DSRCHANDLER_H_ */
