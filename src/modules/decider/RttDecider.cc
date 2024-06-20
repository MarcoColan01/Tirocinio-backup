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

#include "RttDecider.h"

Define_Module(RttDecider);

void RttDecider::initialize(int stage)
{
    // TODO - Generated method body
    BaseDecider::initialize(stage);
    if (stage!= DECIDER_LOCAL_STAGE)
           return;

    RttThreshold = par("RttThreshold");
}

void RttDecider::registerValue(std::string featureName, double simtime, double value){
    if(strcmp(featureName.c_str(), "cellularRtt") == 0){
        RttValue = value;
     }
}
void RttDecider::evaluateCellularRatReliability(){
    cellularReliabilityLevel = RttValue < RttThreshold? RATReliabilityLevel::HIGH : RATReliabilityLevel::LOW;

}
