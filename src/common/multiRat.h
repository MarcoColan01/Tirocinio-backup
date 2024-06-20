/*
 * common.h
 *
 *  Created on: Oct 26, 2023
 *      Author: christian
 */

#ifndef MODULES_DECIDER_COMMONS_H_
#define MODULES_DECIDER_COMMONS_H_

#define DECIDER_BASE_NUM_INIT_STAGES 1
#define DECIDER_AI_NUM_INIT_STAGES 3

#define DECIDER_LOCAL_STAGE 0
#define DECIDER_AI_CONNECTION_SETUP 1
#define DECIDER_AI_CONNECTION_READY 2


namespace multirat{

enum RATReliabilityLevel {
    HIGH,
    LOW
};


enum SystemType {NONE, CELLULAR, DSRC, MIX};

const SystemType sysTypeVector[] = {NONE, CELLULAR, DSRC, MIX};

typedef struct{
    SystemType systemType;
    double instruction;
} instruction_t;


}
#endif /* MODULES_DECIDER_COMMONS_H_ */
