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

#include "ExtendedVeinsInetManager.h"

#include <cstdlib>
#include <string.h>
#include <stdlib.h>

Define_Module(ExtendedVeinsInetManager);

//void ExtendedVeinsInetManager::initialize(int stage){
//    veins::VeinsInetManager::initialize(stage);
//}

int ExtendedVeinsInetManager::getPortNumber() const{
    Enter_Method("getPortNumber");
    // search for externally configured traci port
    char* envPortList = std::getenv("VEINS_TRACI_PORT_LIST");

    int runnnumber = atoi(getEnvir()->getConfigEx()->getVariable(CFGVAR_RUNNUMBER));
//    EV_INFO << getEnvir()->getConfigEx()->getVariable(CFGVAR_RUNNUMBER) << endl;
    if (envPortList != nullptr) {
        std::vector<int> portNumberList;
        char* token =strtok(envPortList, " ,");
        while (token != NULL){
            portNumberList.push_back(atoi(token));
            token =strtok(NULL, " ,");
        }

        return portNumberList[runnnumber % portNumberList.size()];
//        EV_INFO << "selected port for run_num " << runnnumber << " is " << portNumberList[runnnumber % portNumberList.size()] << endl;
//        EV_INFO << env_port_list << endl;
//        port = std::atoi(env_port);
//        return port;
    }

    return veins::VeinsInetManager::getPortNumber();

}
