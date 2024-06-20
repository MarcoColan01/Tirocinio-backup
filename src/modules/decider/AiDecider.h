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

#ifndef __SIMULATOR_5G_V2X_AIDECIDER_H_
#define __SIMULATOR_5G_V2X_AIDECIDER_H_

#include <omnetpp.h>
#include "modules/decider/BaseDecider.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"

#include "modules/decider/aiDeciderUtils/communicationProtocol.h"
#include "modules/decider/GlobalAiDeciderManager.h"

using namespace omnetpp;
using namespace multirat;


class AiDecider : public BaseDecider
{
public:
    ~AiDecider();

protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return DECIDER_AI_NUM_INIT_STAGES; }
    //    virtual void handleMessage(cMessage *msg) override;
    virtual void registerValue(std::string featureName, double simtime, double value) override;
    virtual void evaluateCellularRatReliability() override;
    //    virtual void evaluateDsrcInstructionReliability(double instruction) override;
    //    virtual void evaluate(const BaseDecider::Status &status) override;

    simsignal_t predictedCellularInstructionDifferenceSignal;
    simsignal_t predictedDsrcInstructionDifferenceSignal;

    simtime_t lastCellularEvaluation;


private:
    GlobalPlatoonsManager *gpm;
    GlobalAiDeciderManager *gAiDecider;

    double reliabilityThreshold;
};

#endif
