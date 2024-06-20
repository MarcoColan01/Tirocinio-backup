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

package simulator_5g_v2x.modules.extendedveins;

//
// TODO auto-generated module
//
simple BackgroundVehiclesGenerator
{
    @class(BackgroundVehiclesGenerator);
    int numVehicles = default(0);
    string vehicleTypeId = default("bg_vehicle");
    string vehicleRouteId = default("route_traffic");
    double emitSpeed @unit(mps) = default(25mps);
    int emitLane = default(1);
    volatile double emitInterval @unit(s) = default(5s);
    double generationTimeStart @unit(s) = default(10s);

    @display("i=block/network2");
}
