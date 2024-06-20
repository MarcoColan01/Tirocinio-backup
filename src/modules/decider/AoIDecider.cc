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

#include "AoIDecider.h"

Define_Module(AoIDecider);

vector<vector<double> >AoIAllValues(3, vector<double>());

void AoIDecider::initialize(int stage)
{
    // TODO - Generated method body
    BaseDecider::initialize(stage);
    if (stage!= DECIDER_LOCAL_STAGE)
           return;

    AoIThresholdUL = par("AoIThresholdUL");
    AoIThresholdDL = par("AoIThresholdDL");
    AoIThresholdMetric = par("AoIThresholdMetric").stringValue();
    AoIValuesWindow = par("AoIValuesWindow");
}

void AoIDecider::registerValue(std::string featureName, double simtime, double value){
    if(whichAoIValue(featureName)!=-1){
        if(AoIAllValues[whichAoIValue(featureName)].size()<AoIValuesWindow){
            if(value>0){
               AoIAllValues[whichAoIValue(featureName)].push_back(value);
               //std::cout << "value " <<AoIAllValues[whichAoIValue(featureName)].size()<<endl;
            }
        }
        else{
            if(strcmp(AoIThresholdMetric.c_str(), "mean") == 0){
                LeaderVehicleAoi = getMean(AoIAllValues[0]);
                PrecedingVehicleAoi = getMean(AoIAllValues[1]);
                ThisVehicleAoi = getMean(AoIAllValues[2]);
            }
            else if(strcmp(AoIThresholdMetric.c_str(), "variance") == 0){
                LeaderVehicleAoi = getVariance(AoIAllValues[0]);
                PrecedingVehicleAoi = getVariance(AoIAllValues[1]);
                ThisVehicleAoi = getVariance(AoIAllValues[2]);
            }
            else if(strcmp(AoIThresholdMetric.c_str(), "stddev") == 0){
                 LeaderVehicleAoi = sqrt(getVariance(AoIAllValues[0]));
                 PrecedingVehicleAoi = sqrt(getVariance(AoIAllValues[1]));
                 ThisVehicleAoi = sqrt(getVariance(AoIAllValues[2]));
            }
            else {
                throw new cRuntimeError("Unsupported metric");
            }

            AoIAllValues[whichAoIValue(featureName)].erase(AoIAllValues[whichAoIValue(featureName)].begin());
        }
    }
    else if(strcmp(featureName.c_str(), "cellularInstructionAoi") == 0){
            InstructionAoi = value;
        }
}

int AoIDecider::whichAoIValue(std::string featureName){
    if(strcmp(featureName.c_str(), "cellularLeaderVehicleAoi") == 0){
        return 0;
    }
    else if(strcmp(featureName.c_str(), "cellularPrecedingVehicleAoi") == 0){
       return 1;
    }
    else if(strcmp(featureName.c_str(), "cellularThisVehicleAoi") == 0){
       return 2;
    }
    return -1;
}

double AoIDecider::getMean(const vector<double> &vec){
    return accumulate (vec.begin(), vec.end(), 0.0) / vec.size();
}

double AoIDecider::getVariance(const vector<double> &vec){
    double variance;
    double mean = getMean(vec);
    for(int i = 0; i < vec.size(); i++) {
        variance += pow(vec[i] - mean, 2);
    }
    return variance;
}

void AoIDecider::evaluateCellularRatReliability(){
    cellularReliabilityLevel = max(LeaderVehicleAoi,max(PrecedingVehicleAoi,ThisVehicleAoi)) < AoIThresholdUL
            && InstructionAoi < AoIThresholdDL ?  RATReliabilityLevel::HIGH : RATReliabilityLevel::LOW ;
}


