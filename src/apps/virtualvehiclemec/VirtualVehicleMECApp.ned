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

package simulator_5g_v2x.apps.virtualvehiclemec;

import inet.applications.contract.IApp;
import simu5g.nodes.mec.MECPlatform.IMECApp;

simple VirtualVehicleMECApp like IMECApp, IApp
{
    parameters:
        @signal[statusAgeOfInfoSignal](type="double");
        @signal[statusDiscardedSignal](type="bool");
        @signal[vehicleStatusPacketDelay](type="double");
        
		@statistic[statusAgeOfInfo](title="status age of info"; source="statusAgeOfInfoSignal"; record=vector,stats; interpolationmode=none);
		@statistic[statusDiscarded](title="status discarded"; source="statusDiscardedSignal"; record=vector,stats; interpolationmode=none);
		@statistic[vehicleStatusPacketDelay](title="Delay of status packet from vehicle"; source="vehicleStatusPacketDelay"; record=vector,stats; interpolationmode=none);
        int mecAppId;
        int mecAppIndex = default(0);
        int instructionPacketSize = default(200);
        
        int timeToLive = default(-1);
        int dscp = default(-1);
        int tos = default(-1);

		double minStatusDistance @unit("s") = default(0.05s);
		double startAckTimeout @unit("s") = default(2s);
		
		double packetDropRate = default(0);
        
        string mp1Address;
        int mp1Port;
        
        int localUePort;
        
	
		//resource required infos
        double requiredRam @unit("B");
        double requiredDisk @unit("B");
        double requiredCpu;
	gates:
	  input mePlatformIn;
	  output mePlatformOut;
	  
	  input socketIn;
	  output socketOut;
}
