
package simulator_5g_v2x.modules.hostconfigurator;

import inet.networklayer.configurator.ipv4.HostAutoConfigurator;


simple MultiNicHostAutoConfigurator extends HostAutoConfigurator
{
    parameters:
        string addressesBase = default("11.0.0.0 10.0.0.0");    // lista indirizzi base per ciascuna interfaccia
        string applyMcastGroupsTo = default("");
        
     @class(MultiNicHostAutoConfigurator);
}

