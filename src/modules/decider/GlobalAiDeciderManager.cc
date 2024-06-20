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

#include "GlobalAiDeciderManager.h"

using namespace ai_decider_api;

Define_Module(GlobalAiDeciderManager);


void GlobalAiDeciderManager::initialize()
{
    run_id = getEnvir()->getConfigEx()->getVariable(CFGVAR_RUNID);
}


void GlobalAiDeciderManager::finish(){
    if (connectedAndInitialized){
        //send simulation data destroy message
        end_simulation_request requestMessage;
        requestMessage.message_payload.run_id = run_id;

        sendAndGet<end_simulation_request,ack_response>(requestMessage);
        socket.close();
    }
}

void GlobalAiDeciderManager::registerVehicleAiDecider(){
    if (connectedAndInitialized)  //make sure that this is performed only once!!
        return;

    auto protocol = par("protocol").stdstringValue();
    auto host = par("host").stdstringValue();
    auto port = par("port").intValue();
    auto timeout_ms = (int)(par("communicationTimeoutms").doubleValue() *1000);

    context = zmq::context_t {1};
    socket = zmq::socket_t{context, zmq::socket_type::req};

    socket.setsockopt(ZMQ_RCVTIMEO, timeout_ms); // set timeout to value of timeout_ms
    socket.setsockopt(ZMQ_SNDTIMEO, timeout_ms); // set timeout to value of timeout_ms
    std::string addr = protocol + "://" + host + ":" + std::to_string(port);
    socket.connect(addr);


    // send simulation run initialization
    init_simulation_request requestMessage;
    requestMessage.message_payload.run_id = run_id;

    sendAndGet<init_simulation_request,ack_response>(requestMessage);
    connectedAndInitialized = true;
}


void GlobalAiDeciderManager::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
