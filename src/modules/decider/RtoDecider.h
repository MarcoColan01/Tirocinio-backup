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

#ifndef __SIMULATOR_5G_V2X_RTODECIDER_H_
#define __SIMULATOR_5G_V2X_RTODECIDER_H_

#include <omnetpp.h>
#include "modules/decider/BaseDecider.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class RtoDecider : public BaseDecider
{
    private:
    double RtoThreshold;
    int RtoNumber;
    int RtoActualValue;
    cMessage * timerTimeOut;
    protected:
    virtual void initialize(int stage) override;
    virtual void registerValue(std::string featureName, double simtime, double value) override;
    virtual void evaluateCellularRatReliability() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
