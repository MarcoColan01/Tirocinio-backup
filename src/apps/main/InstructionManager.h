/*
 * InstructionManager.h
 *
 *  Created on: Oct 30, 2023
 *      Author: christian
 */

#ifndef APPS_MAIN_INSTRUCTIONMANAGER_H_
#define APPS_MAIN_INSTRUCTIONMANAGER_H_

#include <omnetpp.h>
#include "modules/decider/BaseDecider.h"




class InstructionManager {
protected:
    double lastCellularInstruction;
    double lastDsrcInstruction;
    BaseDecider *decider;
//    int hysteresisThreshold;

    class Mode {
    public:
        virtual instruction_t getBestInstruction(InstructionManager *im) = 0;
    };

    class AutoMode: public Mode {
    public:
        AutoMode(int hysteresisThreshold);
        instruction_t getBestInstruction(InstructionManager *im) override;

    private:
        SystemType currentRAT  = SystemType::CELLULAR;
        std::map<SystemType, int> hysteresisCounter;
        int hysteresisThreshold;
        void updateHysteresisCounter(SystemType prev, SystemType best);
        bool isHysteresisThresholdHit(SystemType ratType);
    };

    class CellularOnlyMode: public Mode {
    public:
        instruction_t getBestInstruction(InstructionManager *im) override;
    };

    class CellularOnlyForcedMode: public Mode {
    public:
        instruction_t getBestInstruction(InstructionManager *im) override;
    };

    class DsrcOnlyMode: public Mode {
    public:
        instruction_t getBestInstruction(InstructionManager *im) override;
    };

    class DsrcOnlyForcedMode: public Mode {
    public:
        instruction_t getBestInstruction(InstructionManager *im) override;
    };

    InstructionManager::Mode *selectionMode;


    InstructionManager::Mode* getModeFromParam(cModule* appModule);

    double getLastInstructionOfSystem(SystemType sysType);
    bool isSystemReliable(SystemType sysType);

    public:
    /*
     * Passing app module pointer simplifies "extension" of Instruction Manager component
     * InstructionManager is not a cModule; thus all configuration parameters must be defined in APP module
     */
    InstructionManager(BaseDecider *decider, cModule* appModule);
    virtual ~InstructionManager();

    void setCellularInstruction(double instruction);
    void setDsrcInstruction(double instruction);

    // Get the best instruction according to the reliability level of the different RAT systems
    instruction_t getBestInstruction();

};

#endif /* APPS_MAIN_INSTRUCTIONMANAGER_H_ */
