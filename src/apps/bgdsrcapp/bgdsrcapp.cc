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

#include "bgdsrcapp.h"


Define_Module(Bgdsrcapp);

using namespace inet;
using namespace omnetpp;
using namespace std;
using namespace veins;


void Bgdsrcapp::handleStartOperation(inet::LifecycleOperation* doneCallback)
{

    VeinsInetApplicationBase::handleStartOperation(doneCallback);

    auto callback = [this]() {

        //creo payload
        auto bgCarPayload = makeShared<VeinsInetSampleMessage>();
        bgCarPayload->setChunkLength(B(par("packetSize").intValue()));
        bgCarPayload->setRoadId("route_platoon");

        //creo pacchetto
        auto bgCarPckt = createPacket("bgCarPacket");
        bgCarPckt->insertAtBack(bgCarPayload);
        sendPacket(move(bgCarPckt));

    };


    //invio pacchetto ad un intervallo randomico compreso tra 1ms e 10ms (circa)
    //a cui sommo una costante passata come parametro di simulazione
    //uniform(SimTime(-50, SIMTIME_US), SimTime(50,SIMTIME_US))
    timerManager.create(TimerSpecification(callback).relativeStart(uniform(0.00100,0.10000)).interval(par("transmissionInterval").doubleValue()));
    //timerManager.create(TimerSpecification(callback).interval(double(par("constantForInterval")) + uniform(0.00100,0.01000)));
    //std::cout << "costante: " << double(par("constantForInterval")) << " numero estratto: " << k - double(par("constantForInterval")) << " k: " << k  << endl;





}


