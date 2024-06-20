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
simple BaseDecider like IDecider
{  
    @class(BaseDecider);
    
    //double targetDistance @unit(m); // TODO is this necessary?
    double minRatEvaluationInterval @unit("s") = default(0.5 s);
    
    
    // SIGNALS
    // cellular
    @signal[cellularThisVehicleAoiSignal](type="double");
    @signal[cellularPrecedingVehicleAoiSignal](type="double");
    @signal[cellularLeaderVehicleAoiSignal](type="double");
    @signal[cellularInstructionAoiSignal](type="double");
    @signal[cellularInstructionDifferenceSignal](type="double");
    @signal[cellularCqiUlSignal](type="double");
    @signal[cellularCqiDlSignal](type="double");
    @signal[cellularRttSignal](type="double");
    
    // dsrc
    @signal[dsrcInstructionDifferenceSignal](type="double");
    @signal[dsrcPrecedingVehicleAoiSignal](type="double");
    @signal[dsrcLeaderVehicleAoiSignal](type="double");
    @signal[dsrcMacQueueingTimeSignal](type="double");
    // TODO ADD MAC LAYER INFO 
    
    // vehicle motion
    @signal[accelerationSignal](type="double");
    @signal[speedSignal](type="double");
    @signal[distanceErrorSignal](type="double");
    
    // decision
    @signal[decisionSystemSignal](type="int");
    @signal[decisionInstructionSignal](type="double");
    
    
    // STATISTICS
    @statistic[cellularCqiUl](title="CQI UL"; source="cellularCqiUlSignal"; record=vector; interpolationmode=none);
    @statistic[cellularCqiDl](title="CQL DL"; source="cellularCqiDlSignal"; record=vector; interpolationmode=none);
    @statistic[cellularRtt](title="cellular RTT"; source="cellularRttSignal"; record=vector; interpolationmode=none);
    @statistic[cellularThisVehicleAoi](title="Cellular this vehicle AOI"; source="cellularThisVehicleAoiSignal"; record=vector; interpolationmode=none);
    @statistic[cellularPrecedingVehicleAoi](title="Cellular preceding vehicle AOI"; source="cellularPrecedingVehicleAoiSignal"; record=vector; interpolationmode=none);
    @statistic[cellularLeaderVehicleAoi](title="Cellular leader vehicle AOI"; source="cellularLeaderVehicleAoiSignal"; record=vector; interpolationmode=none);
    @statistic[cellularInstructionAoi](title="Cellular instruction AOI"; source="cellularInstructionAoiSignal"; record=vector; interpolationmode=none);
    @statistic[cellularInstructionDifference](title="Cellular instruction difference"; source="cellularInstructionDifferenceSignal"; record=vector; interpolationmode=none);
    
    
    @statistic[dsrcPrecedingVehicleAoi](title="DSRC Preceding vehicle AOI"; source="dsrcPrecedingVehicleAoiSignal"; record=vector; interpolationmode=none);
    @statistic[dsrcLeaderVehicleAoi](title="DRSC Leader vehicle AOI"; source="dsrcLeaderVehicleAoiSignal"; record=vector; interpolationmode=none);
    @statistic[dsrcMacQueueingTime](title="DRSC Queueing time"; source="dsrcMacQueueingTimeSignal"; record=vector; interpolationmode=none);
    // TODO ADD MAC LAYER INFO 
    @statistic[dsrcInstructionDifference](title="DSRC instruction difference"; source="dsrcInstructionDifferenceSignal"; record=vector; interpolationmode=none);
    
    
    @statistic[acceleration](title="Acceleration"; source="accelerationSignal"; record=vector; interpolationmode=none);
    @statistic[speed](title="Speed"; source="speedSignal"; record=vector; interpolationmode=none);
    @statistic[distanceError](title="Distance error"; source="distanceErrorSignal"; record=vector; interpolationmode=none);
    
    //decision
    @statistic[decisionSystem](title="RAT system used"; source="decisionSystemSignal";record=vector; interpolationmode=none);
    @statistic[decisionInstruction](title="Acceleration instruction used"; source="decisionInstructionSignal"; record=vector; interpolationmode=none);
}																											  
