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

#ifndef __SIMULATOR_5G_V2X_GLOBALAIDECIDERMANAGER_H_
#define __SIMULATOR_5G_V2X_GLOBALAIDECIDERMANAGER_H_

#include <omnetpp.h>
#include <zmq.hpp>

#include "common/multiRat.h"
#include "modules/decider/aiDeciderUtils/communicationProtocol.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class GlobalAiDeciderManager : public cSimpleModule
{
protected:
    virtual void finish() override;
    virtual void initialize() override;
//    virtual int numInitStages() const override { return DECIDER_AI_NUM_INIT_STAGES; }
    virtual void handleMessage(cMessage *msg) override;

private:
    zmq::socket_t socket;
    zmq::context_t context;
    std::string run_id;

    int vehicleAiDeciderCounter = 0;
    bool connectedAndInitialized = false;

public:
    void registerVehicleAiDecider();


    template<typename REQ, typename REP> REP sendAndGet(REQ requestMessage){
        // all request messages should have 'run_id' field in message payload
        json jsonRequestMessage = requestMessage;
        jsonRequestMessage["message_payload"]["run_id"] = run_id;
        // SEND
        socket.send(zmq::buffer(jsonRequestMessage.dump()), zmq::send_flags::none);

        // RECEIVE
        zmq::message_t reply{};
        if (!socket.recv(reply, zmq::recv_flags::none)){
            throw std::runtime_error("Timeout ERROR");
        }
        json jsonResp = json::parse(reply.to_string());
        return jsonResp.get<REP>();

    }

};

#endif
