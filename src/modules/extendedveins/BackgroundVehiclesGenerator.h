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

#ifndef __SIMULATOR_5G_V2X_BACKGROUNDVEHICLESMANAGER_H_
#define __SIMULATOR_5G_V2X_BACKGROUNDVEHICLESMANAGER_H_

#include <string>
#include <omnetpp.h>
#include "veins_inet/veins_inet.h"
#include "veins_inet/VeinsInetManager.h"

using namespace omnetpp;
using namespace veins;
using namespace inet;
/**
 * TODO - Generated class
 */
class BackgroundVehiclesGenerator : public cSimpleModule
{
public:
    ~BackgroundVehiclesGenerator();


protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {return inet::NUM_INIT_STAGES;}
    virtual void handleMessage(cMessage *msg) override;

private:
    int generatorIndex;
    int numVehiclesToGenerate;
    int numGenerated = 0;
    std::string vehicleTypeId;
    std::string vehicleRouteId;
    double emitSpeed;
    int emitLane;

    cMessage *generationMessage;
    VeinsInetManager* veinsInetManagerMod;

    void addNewVechile();
};

#endif
