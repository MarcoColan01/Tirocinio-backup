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

#include "AiDecider.h"


#include <stdexcept>

Define_Module(AiDecider);

using namespace ai_decider_api;

AiDecider::~AiDecider(){
    //socket
}



void AiDecider::initialize(int stage)
{
    BaseDecider::initialize(stage);

    if (stage == DECIDER_LOCAL_STAGE){
        gpm = check_and_cast<GlobalPlatoonsManager *>(getModuleByPath("<root>.globalPlatoonsManager"));
        gAiDecider = check_and_cast<GlobalAiDeciderManager*>(getModuleByPath("<root>.globalAiDeciderManager"));
        gAiDecider->registerVehicleAiDecider();
        // OTHER PARAMETERS
        reliabilityThreshold = par("reliabilityThreshold").doubleValue();
        //SIGNAL inizialization
        predictedCellularInstructionDifferenceSignal = registerSignal("predictedCellularInstructionDifferenceSignal");
        predictedDsrcInstructionDifferenceSignal = registerSignal("predictedDsrcInstructionDifferenceSignal");

        lastCellularEvaluation = simTime();
    }


    if (stage == DECIDER_AI_CONNECTION_READY){
        init_vehicle_request requestMessage;
        requestMessage.message_payload.vehicle_id = getPhysicalCarId();
        requestMessage.message_payload.cellular_ai_model_name = par("cellularModelName").stdstringValue();
        requestMessage.message_payload.dsrc_ai_model_name = par("dsrcModelName").stdstringValue();

        gAiDecider->sendAndGet<init_vehicle_request, ack_response>(requestMessage);
    }
}



void AiDecider::registerValue(std::string featureName, double simtime, double value){
    feature_data_request requestMessage;
    requestMessage.message_payload.vehicle_id = getPhysicalCarId();
    requestMessage.message_payload.feature_name = featureName;
    requestMessage.message_payload.timestamp = simtime;
    requestMessage.message_payload.value = value;
    gAiDecider->sendAndGet<feature_data_request, ack_response>(requestMessage);
}


void AiDecider::evaluateCellularRatReliability(){
    Enter_Method("evaluateCellularInstructionReliability");
    if (!gpm->hasVehicleByPhysicalVehicleId(getPhysicalCarId())){
        return; // Vehicle has not been added to the platoon yet!
    }


    auto v_info = gpm->getVehicleInfoByPhysicalVehicleId(getPhysicalCarId());
    evaluate_request requestMessage;
    requestMessage.message_payload.vehicle_id = getPhysicalCarId();
    requestMessage.message_payload.vehicle_position = gpm->getPositionByPhysicalVehicleId(getPhysicalCarId());
    requestMessage.message_payload.platoon_length = gpm->platoonSize(v_info.platoonId);
    auto response = gAiDecider->sendAndGet<evaluate_request, prediction_response>(requestMessage);

    if (response.message_payload.cellular_prediction_valid){
        double predictedValue = response.message_payload.cellular_value;
        // emit signal
        emit(predictedCellularInstructionDifferenceSignal, predictedValue);
        // Reliability evaluation
        if ( predictedValue > reliabilityThreshold)// || predictedValue < 0)
            cellularReliabilityLevel = RATReliabilityLevel::LOW;
        else
            cellularReliabilityLevel = RATReliabilityLevel::HIGH;
    }

    if (response.message_payload.dsrc_prediction_valid){
        double predictedValue = response.message_payload.dsrc_value;
        // emit signal
        emit(predictedDsrcInstructionDifferenceSignal, predictedValue);
        // Reliability evaluation
        if ( predictedValue > reliabilityThreshold || predictedValue < 0)
            dsrcReliabilityLevel = RATReliabilityLevel::LOW;
        else
            dsrcReliabilityLevel = RATReliabilityLevel::HIGH;
    }
}

