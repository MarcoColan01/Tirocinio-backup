/*
 * communicationProtocol.h
 *
 *  Created on: Oct 25, 2023
 *      Author: christian
 */

#ifndef MODULES_DECIDER_AIDECIDERUTILS_COMMUNICATIONPROTOCOL_H_
#define MODULES_DECIDER_AIDECIDERUTILS_COMMUNICATIONPROTOCOL_H_


#include "lib/json.hpp"

using json = nlohmann::json;


namespace ai_decider_api
{
    /*BASE*/
    struct init_simulation {
        std::string run_id;     // some unique identifier of the running simulation
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(init_simulation, run_id)

    struct end_simulation {
        std::string run_id;     // some unique identifier of the running simulation
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(end_simulation, run_id)


    struct init_vehicle {
        std::string vehicle_id;
        std::string cellular_ai_model_name;
        std::string dsrc_ai_model_name = "";  // TODO to be changed when models are ready!!!
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(init_vehicle, vehicle_id, cellular_ai_model_name, dsrc_ai_model_name)


    struct feature_data {
        std::string vehicle_id;
        std::string message_type = "feature_data";
        std::string feature_name;
        double timestamp;
        double value;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(feature_data, vehicle_id, message_type, feature_name, timestamp, value)


    struct evaluate {
        std::string vehicle_id;
        std::string message_type = "evaluate";
        int vehicle_position;
        int platoon_length;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(evaluate, vehicle_id, message_type, vehicle_position, platoon_length)


    struct prediction {
        std::string vehicle_id;
        double cellular_value;
        bool cellular_prediction_valid;
        double dsrc_value;
        bool dsrc_prediction_valid;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(prediction, vehicle_id, cellular_value, cellular_prediction_valid, dsrc_value, dsrc_prediction_valid)

    /*
    *   REQUESTS
    */
    struct init_simulation_request {
        std::string message_type = "init_simulation";
        init_simulation message_payload;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(init_simulation_request, message_type, message_payload)


    struct end_simulation_request {
            std::string message_type = "end_simulation";
            init_simulation message_payload;
        };
        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(end_simulation_request, message_type, message_payload)


    struct init_vehicle_request {
        std::string message_type = "init_vehicle";
        init_vehicle message_payload;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(init_vehicle_request, message_type, message_payload)

    struct feature_data_request {
        std::string message_type = "vehicle_specific";
        feature_data message_payload;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(feature_data_request, message_type, message_payload)


    struct evaluate_request {
        std::string message_type = "vehicle_specific";
        evaluate message_payload;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(evaluate_request, message_type, message_payload)

    /*
    *   RESPONSE
    */
    struct ack_response {
        std::string message_type;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ack_response, message_type)

    struct prediction_response {
        std::string message_type;
        prediction message_payload;
    };
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(prediction_response, message_type, message_payload)

}



#endif /* MODULES_DECIDER_AIDECIDERUTILS_COMMUNICATIONPROTOCOL_H_ */
