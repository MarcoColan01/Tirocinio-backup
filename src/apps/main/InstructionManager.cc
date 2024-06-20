/*
 * instructionManager.cc
 *
 *  Created on: Oct 30, 2023
 *      Author: christian
 */

#include "InstructionManager.h"

#define NEUTRAL_INSTRUCTION 0.0

#define AUTO_MODE "auto"
#define CELLULAR_ONLY_MODE "cellularOnly"
#define CELLULAR_ONLY_FORCED_MODE "cellularOnlyForced"
#define DSRC_ONLY_MODE "dsrcOnly"
#define DSRC_ONLY_FORCED_MODE "dsrcOnlyForced"


InstructionManager::InstructionManager(BaseDecider *decider, cModule *appModule) {
    this->decider = decider;
    this->selectionMode = getModeFromParam(appModule);
}

InstructionManager::~InstructionManager() {
    delete selectionMode;
}


void InstructionManager::setCellularInstruction(double instruction){
    lastCellularInstruction = instruction;
}
void InstructionManager::setDsrcInstruction(double instruction){
    lastDsrcInstruction = instruction;
}

double InstructionManager::getLastInstructionOfSystem(SystemType sysType){
    switch (sysType){
    case CELLULAR:
        return lastCellularInstruction;
    case DSRC:
        return lastDsrcInstruction;
    case NONE:
        return NEUTRAL_INSTRUCTION;
    case MIX:
        throw new cRuntimeError("Unimplemented SystemType");
    }
}


bool InstructionManager::isSystemReliable(SystemType sysType){
    switch (sysType){
    case CELLULAR:
        return decider->isCellularReliable();
    case DSRC:
        return decider->isDsrcReliable();
    case NONE:
        return true;
    case MIX:
        throw new cRuntimeError("Unimplemented SystemType");
    }
}



InstructionManager::Mode* InstructionManager::getModeFromParam(cModule* appModule){
    // simple string comparison
    auto modeParamValue = appModule->par("instructionMngMode").stringValue();
    if (strcmp(modeParamValue, AUTO_MODE) == 0) return new InstructionManager::AutoMode(appModule->par("instructionMngHysteresisThreshold").intValue());
    if (strcmp(modeParamValue, CELLULAR_ONLY_MODE) == 0) return new InstructionManager::CellularOnlyMode();
    if (strcmp(modeParamValue, CELLULAR_ONLY_FORCED_MODE) == 0) return new InstructionManager::CellularOnlyForcedMode();
    if (strcmp(modeParamValue, DSRC_ONLY_MODE) == 0) return new InstructionManager::DsrcOnlyMode();
    if (strcmp(modeParamValue, DSRC_ONLY_FORCED_MODE) == 0) return new InstructionManager::DsrcOnlyForcedMode();

    throw new cRuntimeError("Unknown instruction mode!");
}


instruction_t InstructionManager::getBestInstruction(){
    auto bestInstruction = selectionMode->getBestInstruction(this);
    // informing the decider so it can save some STATS
    decider->registerUsedInstruction(bestInstruction);
    return bestInstruction;
}


/**
 * AUTO MODE
 */
InstructionManager::AutoMode::AutoMode(int hysteresisThreshold){
    this->hysteresisThreshold = hysteresisThreshold;
    //initialize the hysteresis counter map
    for (auto s : multirat::sysTypeVector){
        hysteresisCounter[s] = 0;
    }

}

bool InstructionManager::AutoMode::isHysteresisThresholdHit(SystemType sytType){
    return hysteresisCounter[sytType] >= hysteresisThreshold;
}

void InstructionManager::AutoMode::updateHysteresisCounter(SystemType prev, SystemType best){
    for (auto const& el : hysteresisCounter){
        if (el.first == best){ hysteresisCounter[el.first]++; }
        else if (prev!= SystemType::NONE) {hysteresisCounter[el.first] = 0;}
    }
}


instruction_t InstructionManager::AutoMode::getBestInstruction(InstructionManager *im){
    // TODO Add more complex decision process if needed
    SystemType systemPriorities[] = {CELLULAR, DSRC, NONE};
    SystemType bestSystem = SystemType::NONE;

    // find the best reiliable system according to the priority
    for(auto sys : systemPriorities){
        if (im->isSystemReliable(sys)){
            bestSystem = sys;
            break;
        }
    }
    //    std::cout << im->decider->getFullPath() << " "
    //            << (std::round(im->decider->getSimulation()->getSimTime().dbl() * 1000.0) / 1000.0) << "\t"
    //            << bestSystem << " (hyst: " << hysteresisCounter[bestSystem] << ")" << endl;
    // Apply hysteresis
    if (currentRAT == bestSystem){
        //        std::cout << "\t\t" << "Use best system "<<  currentRAT << endl;
        return instruction_t{bestSystem, im->getLastInstructionOfSystem(bestSystem)};
    } else{
        updateHysteresisCounter(currentRAT, bestSystem);
        if (isHysteresisThresholdHit(bestSystem)){
            std::cout << im->decider->getFullPath() << " "
                    << (std::round(im->decider->getSimulation()->getSimTime().dbl() * 1000.0) / 1000.0)
                    << "\t" << "Switch from "<<  currentRAT << " to " << bestSystem << endl;
            currentRAT = bestSystem;    // Switch to best system
            hysteresisCounter[bestSystem] = 0; // reset
            return instruction_t{bestSystem, im->getLastInstructionOfSystem(bestSystem)};
        }
    }
    // continue with the current RAT if best system could not be used
    //    std::cout << "\t\t" << "Use current system "<<  currentRAT << endl;
    // TODO if currentRAT reliable
    //    if (im->isSystemReliable(currentRAT))
    return instruction_t{currentRAT, im->getLastInstructionOfSystem(currentRAT)};
    //    return instruction_t{SystemType::NONE, NEUTRAL_INSTRUCTION};
}

/**
 * CELLULAR ONLY
 */
instruction_t InstructionManager::CellularOnlyMode::getBestInstruction(InstructionManager *im){
    if (im->isSystemReliable(CELLULAR)){
        return instruction_t{SystemType::CELLULAR, im->getLastInstructionOfSystem(CELLULAR)};
    }
    return instruction_t{SystemType::NONE, NEUTRAL_INSTRUCTION};
}

/**
 * CELLULAR ONLY FORCED
 */
instruction_t InstructionManager::CellularOnlyForcedMode::getBestInstruction(InstructionManager *im){
    return instruction_t{SystemType::CELLULAR, im->lastCellularInstruction};
}

/**
 * DSRC ONLY
 */
instruction_t InstructionManager::DsrcOnlyMode::getBestInstruction(InstructionManager *im){
    if (im->decider->isDsrcReliable()){
        return instruction_t{SystemType::DSRC, im->lastDsrcInstruction};
    }
    return instruction_t{SystemType::NONE, NEUTRAL_INSTRUCTION};
}
/**
 * DSRC ONLY FORCED
 */
instruction_t InstructionManager::DsrcOnlyForcedMode::getBestInstruction(InstructionManager *im){
    return instruction_t{SystemType::DSRC, im->lastDsrcInstruction};
}

