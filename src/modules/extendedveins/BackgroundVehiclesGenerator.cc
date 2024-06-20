
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

#include "BackgroundVehiclesGenerator.h"

#include "veins/modules/mobility/traci/TraCIConstants.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

Define_Module(BackgroundVehiclesGenerator);


BackgroundVehiclesGenerator::~BackgroundVehiclesGenerator(){
}


void BackgroundVehiclesGenerator::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL){
        numVehiclesToGenerate = par("numVehicles").intValue();
        vehicleTypeId = par("vehicleTypeId").stdstringValue();
        vehicleRouteId = par("vehicleRouteId").stdstringValue();
        emitSpeed = par("emitSpeed").doubleValue();
        emitLane = par("emitLane").intValue();
        generatorIndex = getIndex();
    }

    if (stage == inet::INITSTAGE_LAST){
        veinsInetManagerMod = check_and_cast<VeinsInetManager*>(getModuleByPath("<root>.veinsManager"));

        if (numVehiclesToGenerate > 0){
            generationMessage = new cMessage("generateBgVehicle");
            scheduleAfter(par("generationTimeStart").doubleValue(), generationMessage);
        }
    }
}

void BackgroundVehiclesGenerator::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && msg == generationMessage){
        EV_INFO << "Generation of BG vehicle " << numGenerated << endl;
        addNewVechile();
        numGenerated++;
        if (numGenerated < numVehiclesToGenerate)
            scheduleAfter(par("emitInterval").doubleValue(), generationMessage);
    }
}

void BackgroundVehiclesGenerator::addNewVechile()
{
    std::string vehicleId = "bgCar_"+std::to_string(generatorIndex)+ "-" + std::to_string(numGenerated);
    int emitPos = veins::TraCIConstants::DEPARTFLAG_POS_BASE;
    veinsInetManagerMod->getCommandInterface()->addVehicle(vehicleId, vehicleTypeId, vehicleRouteId, simTime(), emitPos, emitSpeed, emitLane);
}

