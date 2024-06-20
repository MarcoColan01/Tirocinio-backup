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

#include "RtoDecider.h"

Define_Module(RtoDecider);


void RtoDecider::initialize(int stage)
{
    // TODO - Generated method body
    BaseDecider::initialize(stage);
    if (stage!= DECIDER_LOCAL_STAGE)
           return;
    RtoThreshold = par("RtoThreshold");
    RtoNumber = par("RtoNumber").intValue();
    timerTimeOut = new cMessage("RtoTimer");
    RtoActualValue = RtoNumber;

}

void RtoDecider::registerValue(std::string featureName, double simtime, double value){
    Enter_Method_Silent("registerValue");
    if(strcmp(featureName.c_str(), "cellularInstructionDifference") == 0){
        if(timerTimeOut->isScheduled()){
            cancelEvent(timerTimeOut);
            if( RtoActualValue <RtoNumber){
                RtoActualValue++;
            }
            //std::cout <<this->carId <<" Recovered "<<RtoActualValue<<endl;
        }
        scheduleAfter(RtoThreshold, timerTimeOut);
    }
}

void RtoDecider::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        if(msg==timerTimeOut){
            RtoActualValue--;
            if(RtoActualValue <0){
               RtoActualValue = 0;
            }
            //std::cout<<this->carId <<" Failed "<<RtoActualValue<<endl;
            //delete msg;
        }
    }
}

void RtoDecider::evaluateCellularRatReliability(){
    cellularReliabilityLevel = RtoActualValue >0? RATReliabilityLevel::HIGH : RATReliabilityLevel::LOW;
}



