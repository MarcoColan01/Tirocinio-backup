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

package simulator_5g_v2x.modules.decider;

//
// TODO auto-generated module
//
simple AiDecider extends BaseDecider
{
    @class(AiDecider);
    
    string host = default("localhost");  // AI server host
    string protocol = default("tcp");
    int port = default(4000); 
    double communicationTimeoutms @unit(s) = default(10s);
    
//    double decisionPeriod @unit(s)= default(1s);
    
    string cellularModelName;
    string dsrcModelName = default("");
    
    double reliabilityThreshold = default(0.05); // this is the threshold for the difference w.r.t. ideal instruction (predicted)
    
    @signal[predictedCellularInstructionDifferenceSignal](type="double");
    @signal[predictedDsrcInstructionDifferenceSignal](type="double");
    
    @statistic[predictedCellularInstructionDifference](title="Predicted cellular difference"; source="predictedCellularInstructionDifferenceSignal";record=vector; interpolationmode=none);
    @statistic[predictedDsrcInstructionDifference](title="Predicted dsrc difference"; source="predictedDsrcInstructionDifferenceSignal";record=vector; interpolationmode=none);
    
}
