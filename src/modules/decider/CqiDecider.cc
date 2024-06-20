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

#include <algorithm>
#include "CqiDecider.h"

Define_Module(CqiDecider);


void CqiDecider::initialize(int stage) {
    BaseDecider::initialize(stage);
    if (stage!= DECIDER_LOCAL_STAGE)
        return;

    cqiThreshold = par("cqiThreshold").intValue();
    expSmoothAlpha = par("expSmoothAlpha");

}

void CqiDecider::registerValue(std::string featureName, double simtime, double value){
    if(strcmp(featureName.c_str(), "cellularCqiUl") == 0){
        if (cqiSmoothedValue >= 0){
            cqiSmoothedValue = expSmoothAlpha * value + (1-expSmoothAlpha) * cqiSmoothedValue;
        }
        else {
            cqiSmoothedValue = value;
        }
    }
}

void CqiDecider::evaluateCellularRatReliability(){
    cellularReliabilityLevel = cqiSmoothedValue < cqiThreshold? RATReliabilityLevel::LOW : RATReliabilityLevel::HIGH;
}

//void CqiDecider::evaluate(const BaseDecider::Status &status){
//    if (status.cellularCqiUl <= cqiThreshold){
//        EV << "UPLINK CQI is " << status.cellularCqiUl << " and is lower or equals that the threshold " << cqiThreshold << endl;
//    }
//}
