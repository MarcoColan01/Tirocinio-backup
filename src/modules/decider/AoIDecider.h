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

#ifndef __SIMULATOR_5G_V2X_AOIDECIDER_H_
#define __SIMULATOR_5G_V2X_AOIDECIDER_H_

#include <omnetpp.h>
#include <numeric>
#include "modules/decider/BaseDecider.h"
using namespace omnetpp;

/**
 * TODO - Generated class
 */
class AoIDecider : public BaseDecider
{
private:
    double AoIThresholdUL,AoIThresholdDL;
    double LeaderVehicleAoi;
    double PrecedingVehicleAoi;
    double ThisVehicleAoi;
    double InstructionAoi;
    string AoIThresholdMetric;
    int AoIValuesWindow;
  protected:
    virtual void initialize(int stage) override;
    virtual void registerValue(std::string featureName, double simtime, double value) override;
    virtual int whichAoIValue(std::string featureName);
    virtual double getMean(const vector<double> &vec);
    virtual double getVariance(const vector<double> &vec);
    virtual void evaluateCellularRatReliability() override;
};

#endif
