//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __SIMULATOR_5G_V2X_MAINAPP_H_
#define __SIMULATOR_5G_V2X_MAINAPP_H_

#include <omnetpp.h>

#include "DsrcHandler.h"
#include "modules/decider/BaseDecider.h"
#include "Handler.h"
#include "SocketWrapper.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/FlatTransmitterBase.h"
#include "inet/physicallayer/wireless/ieee80211/packetlevel/Ieee80211Radio.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "modules/lowlevelcontroller/LowLevelController.h"
#include "InstructionManager.h"

#define V2V_SOCKET 0
#define MEC_SOCKET 1
#define DAPP_SOCKET 2

using namespace omnetpp;
using namespace std;
using namespace inet;
using namespace physicallayer;


/**
 * @brief Applicazione principale del veicolo.
 * L'applicazione si occupa di comunicare con DeviceApp per inizializzare la MEC application.
 * Dopo una prima fase di inizializzazione, l'applicazione avvia l'handler per la gestione V2N.
 * Una volta ricevuti id del platoon e del veicolo dall'handler V2N, l'applicazione instanzia
 * l'handler V2V, che si limiterà inizialmente a trasmettere le informazioni del veicolo ad altri veicoli.
 * Quando l'applicazione scende al di sotto della soglia CQI prefissata, oppure scopre dall'handler offline, 
 * tramite callback, che un veicolo è andato offline, disattiva a tutti gli effetti l'handler V2N e comincia
 * ad utilizzare le istruzioni fornite dall'handler V2V.
 * 
 */
class MainApp : public cSimpleModule,
                UdpSocket::ICallback,
                Handler::OnNewVehiclePacketListener
                {

private:
    map<string, Handler *> activeHandlers;
    map<int, SocketWrapper *> socketsMap;
    LowLevelController *lowLevelController;
    BaseDecider* decider;
    InstructionManager* instructionMng;

    bool firstStatus = true;
    bool firstInstruction = true;
    const char *platoonCarId;
    const char *platoonId;
    set<string> offlineCars;
    double statusUpdateInterval;

    cMessage *selfUpdateMsg;

    void startMECApp();
    void notifyHandlers();
    OnboardControlLawMode getOnboardControlLawMode();

    void handleStatusUpdate(cMessage *msg);
    // Thrown an exception if vehicle has not been correctly registered
    void vehiclePlatoonLogicRegistration(status_t status);

protected:
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

public:

    ~MainApp(){
        cancelAndDelete(selfUpdateMsg);
    }

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket,
            Indication *indication) override {
        throw new cRuntimeError("MainApp::socketErrorArrived");
    }

    virtual void socketClosed(UdpSocket *socket) override {}

    /**
     * @brief Callback per l'Handler
     *
     */
    virtual void onNewInstructionReceived(Handler *handler, const VehicleInstructionPacket *status) override;


    virtual void onNewInstructionReceived(Handler *handler, const vehicle_instruction_t instruction) override;

    /**
     * @brief Callback per l'Handler
     *
     */
    virtual void onPlatoonInfoReceived(
            Handler *handler, const VehiclePlatoonInfoPacket *platoonInfo) override;

};

#endif
