#include "PlatoonService.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include <iostream>
#include <string>
#include <vector>
#include "nodes/mec/utils/httpUtils/httpUtils.h"
#include "common/utils/utils.h"
#include "messages/ServiceMessages_m.h"


Define_Module(PlatoonService);

PlatoonService::PlatoonService(){
}

void PlatoonService::initialize(int stage)
{
    MecServiceBase::initialize(stage);

    if (stage == inet::INITSTAGE_APPLICATION_LAYER) {
        baseUriSubscriptions_ = "/example/Platoon/v1/subscriptions/vehicle";
        platoonsManager = check_and_cast<GlobalPlatoonsManager*>(findModuleByPath("<root>.globalPlatoonsManager"));

        platoonProcessingTimeSignal = registerSignal("platoonProcessingTimeSignal");
    }
}

void PlatoonService::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        ProcessResponseSelfMessage* prsm = dynamic_cast<ProcessResponseSelfMessage*>(msg);
        if(prsm != nullptr){
            list<pair<string, double>> acc = prsm->getResp();
            string triggeringCarId = prsm->getTriggeringCarId();
            string platoonId = prsm->getPlatoonId();
            double calcTime = prsm->getCalcTime();
            //
            for(list<pair<string, double>>::iterator it = acc.begin(); it != acc.end(); it++){
                EV << "CarId: " << it->first << " Acc: " << it->second << endl;
                sendAcceleration(platoonId, it->first, triggeringCarId, it->second,calcTime);
            }

            if (platoonsManager->isPlatoonLeader(platoonId, triggeringCarId)){
                inet::TcpSocket* socket = mecAppSocket.at(pair<string, string>(platoonId, triggeringCarId));
                nlohmann::json jsonBody;
                jsonBody["isLeader"] = true;
                Http::send200Response(socket, jsonBody.dump().c_str());
            }
        }
    }
    MecServiceBase::handleMessage(msg);
}

//Unused
void PlatoonService::handleGETRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket)
{
}
//Received status update from MECApp
void PlatoonService::handlePUTRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket){
    EV_DEBUG << "PlatoonService::handlePUTRequest" << endl;
    std::string uri = currentRequestMessageServed->getUri();
    std::string body = currentRequestMessageServed->getBody();

    if(uri.compare(baseUriSubscriptions_) == 0)
    {
        nlohmann::json jsonBody;
        try
        {
            jsonBody = nlohmann::json::parse(body); // get the JSON structure
        }
        catch(nlohmann::detail::parse_error* e)
        {
            EV_ERROR << "PlatoonService::handlePUTRequest" << e->what() << "\n" << body << std::endl;
            // body is not correctly formatted in JSON, manage it
            Http::send400Response(socket); // bad body JSON
            return;
        }
        EV_DEBUG << "PlatoonService::handlePUTRequest --- Car: " << jsonBody["platoonCarId"] << " Speed: " << jsonBody["speed"] << endl;

        string platoonId = jsonBody["platoonId"].get<string>();
        EV_DEBUG << "RECEIVED platoonId: " << platoonId << endl;
        string platoonCarId = jsonBody["platoonCarId"].get<string>();
        double speed_d = jsonBody["speed"];
        double acceleration_d = jsonBody["acceleration"];
        double distance_d = jsonBody["distance"];
        int sequenceNumber = jsonBody["sequenceNumber"];
        double dataCreatedAt_d = jsonBody["dataCreatedAt"];
        list<pair<string, double>> acc = platoonsManager->updateAndCompute(platoonId, platoonCarId, speed_d, acceleration_d, distance_d,sequenceNumber, dataCreatedAt_d);
        ProcessResponseSelfMessage* msg = new ProcessResponseSelfMessage();
        msg->setPlatoonId(platoonId.c_str());
        msg->setTriggeringCarId(platoonCarId.c_str());
        msg->setCalcTime(simTime().dbl());
        msg->setResp(acc);

        simtime_t responseDelay = par("platoonProcessingTime");
        emit(platoonProcessingTimeSignal, responseDelay);
        scheduleAfter(responseDelay, msg);
        EV_DEBUG << "PlatoonService::handlePUTRequest --- Platoon response messages scheduled at " << simTime()+responseDelay << endl;
    }
    else
    {
        Http::send404Response(socket); //resource not found
    }
}
//MECApp joins platoon
void PlatoonService::handlePOSTRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket){
    Enter_Method("PlatoonService::handlePOSTRequest");
    EV_INFO << "PlatoonService::handlePOSTRequest" << endl;
    std::string uri = currentRequestMessageServed->getUri();
    std::string body = currentRequestMessageServed->getBody();

    if(uri.compare(baseUriSubscriptions_) == 0)
    {
        nlohmann::json jsonBody;
        try
        {
            jsonBody = nlohmann::json::parse(body); // get the JSON structure
        }
        catch(nlohmann::detail::parse_error* e)
        {
            EV_INFO << "PlatoonService::handlePOSTRequest" << e->what() << "\n" << body << std::endl;
            // body is not correctly formatted in JSON, manage it
            Http::send400Response(socket); // bad body JSON
            return;
        }
        //TESTING PlatoonsManager
        std::string physicalId = jsonBody["physicalId"].get<std::string>();
//        std::string carId = jsonBody["carId"].get<std::string>();

        auto plCarInfo = platoonsManager->completeRegistration(physicalId);
        mecAppSocket.insert(pair<pair<string, string>, inet::TcpSocket*>(pair<string, string>(plCarInfo.platoonId, plCarInfo.platoonCarId), socket));
        nlohmann::json jsonResponse;
        jsonResponse["platoonId"] = plCarInfo.platoonId;
        jsonResponse["carId"] = plCarInfo.platoonCarId;

        Http::send201Response(socket, jsonResponse.dump().c_str());
        EV_INFO << "PlatoonService::handlePOSTRequest RESPONDING 201" << endl;
        //        }
    }
    else
    {
        Http::send404Response(socket); //resource not found
        EV_INFO << "PlatoonService::handlePOSTRequest RESPONDING 404" << endl;
    }
}
//Not implemented yet
void PlatoonService::handleDELETERequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket){
}
//Send a PUT request with acceleration update
void PlatoonService::sendAcceleration(string platoonId, string dstCarId, string triggeringCarId, double acceleration,double calcTime){
    EV_INFO << "PlatoonService::sendAcceleration --- to carId: " << dstCarId << endl;
    try{
        inet::TcpSocket* socket = mecAppSocket.at(pair<string, string>(platoonId, dstCarId));
        std::string host = socket->getRemoteAddress().str()+":"+std::to_string(socket->getRemotePort());
        double precedingAoi = calcTime - platoonsManager->getVehicleByPosition(platoonId, atoi(dstCarId.c_str())-1).creationTime;
        double leaderAoi = calcTime - platoonsManager->getVehicleByPosition(platoonId, 0).creationTime;
        double thisAoi = calcTime - platoonsManager->getVehicleByPosition(platoonId, atoi(dstCarId.c_str())).creationTime;

        nlohmann::json jsonBody;
        jsonBody["acceleration"] = acceleration;
        jsonBody["isLeader"] = false;
        jsonBody["thisAoi"] = thisAoi;
        jsonBody["precedingAoi"] = precedingAoi;
        jsonBody["leaderAoi"] = leaderAoi;
        jsonBody["triggeringCarId"] = triggeringCarId;

        if (dstCarId.compare(triggeringCarId) == 0)
            Http::send200Response(socket, jsonBody.dump().c_str());
        else
            Http::sendPutRequest(socket, jsonBody.dump().c_str(), host.c_str(), "carAcceleration/");
    }catch(std::out_of_range* ex){
        EV << "PlatoonService::sendAcceleration --- CarId not found" << endl;
    }
}
void processPlatoonResponse(){

}
void PlatoonService::finish(){
    MecServiceBase::finish();
    return;
}

PlatoonService::~PlatoonService(){
}
