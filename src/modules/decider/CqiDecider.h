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

#ifndef __SIMULATOR_5G_V2X_CQIDECIDER_H_
#define __SIMULATOR_5G_V2X_CQIDECIDER_H_

#include <omnetpp.h>

//#include "util/RingQueue.h"
#include "modules/decider/BaseDecider.h"

#define MAX_LEN 50
#define THIS_VEHICLE 0
#define PRECEDING_VEHICLE 1
#define LEADER_VEHICLE 2

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class CqiDecider : public BaseDecider {
    // TODO: decider v2v (aggiungere channel busy time)

private:
    int cqiThreshold;
    double expSmoothAlpha;
    double cqiSmoothedValue = -1.0; //negative value means not set yet


protected:
    virtual void initialize(int stage) override;
    virtual void registerValue(std::string featureName, double simtime, double value) override;
    virtual void evaluateCellularRatReliability() override;
};

#endif
