package simulator_5g_v2x.modules;

import simulator_5g_v2x.modules.dependencyGraph.DependencyGraph;
import simulator_5g_v2x.modules.controlLaw.ControlLaw;
import simulator_5g_v2x.modules.platooncontroller.PlatoonController;

module Platoon{
    parameters:
        @display("i=veins/node/trafficlight,,0;bgb=,,,,0");
        string graphType;
        string controlLawType;

    submodules:
        platoonController: PlatoonController {
            @display("p=171,50");
        }
        dependencyGraph: <graphType> like DependencyGraph {
            @display("p=55,156");
        }
        controlLaw: <controlLawType> like ControlLaw {
            @display("p=284,156");
        }
}
