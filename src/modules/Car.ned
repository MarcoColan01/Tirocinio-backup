package simulator_5g_v2x.modules;
import simu5g.nodes.NR.NRUe;
import simulator_5g_v2x.modules.hostconfigurator.MultiNicHostAutoConfigurator;
import org.car2x.veins.modules.nic.Nic80211p;
import inet.linklayer.contract.IWirelessInterface;
import simulator_5g_v2x.modules.lowlevelcontroller.LowLevelController;
import simulator_5g_v2x.modules.controlLaw.ControlLaw;
import simulator_5g_v2x.modules.powercontroller.PowerController;
import simulator_5g_v2x.modules.decider.IDecider;
import org.car2x.veins.subprojects.veins_inet.VeinsInetCar;
import inet.node.inet.StandardHost;

module Car extends NRUe //StandardHost 
{
    parameters:
        @display("i=device/car,red,0;is=vs;bgb=,,,,0");

        //# Mobility
        mobility.typename = default("ExtendedVeinsInetMobility");
        //# Network Layer specs
        *.routingTableModule = default(absPath(".ipv4.routingTable"));
       // ipv4.configurator.typename = "MultiNicHostAutoConfigurator";

    submodules:
        controller: LowLevelController {
            @display("p=167.386,59.31;i=block/cogwheel");
        }
}




module HybridCar extends Car
{
    parameters:
 	    //IMPORTANTE: Le GNB sono iscritte  a 224.0.0.1 (all hosts address) e 224.0.0.2 (all routers address)
		//Se si setta uno dei due ip precedenti come multicast, tutti i pacchetti inviati dalla v2vnic vengono letti dalle gnb
        //ipv4.configurator.mcastGroups = default("224.0.0.3"); 
        bool hasDsrcPowerControl = default(false);
    gates:
        input v2vRadioIn @directIn;


    submodules:
        v2vNic: <default("Ieee80211Interface")> like IWirelessInterface {
            @display("p=243.83,589.146,row,150;q=queue");

        }
        
        //controlLaw: <default("CACCControlLaw")> like ControlLaw {
         //   @display("p=126.528,434.94");
        //}
        controlLaw: <default("PLOEGControlLaw")> like ControlLaw {
            @display("p=126.528,434.94");
        }
        powerController: PowerController if hasDsrcPowerControl {
            @display("p=276.78,495.568");
        }
        decider: <default("CqiDecider")> like IDecider {

            @display("i=block/cogwheel;p=75.126,59.31");
        }
    connections allowunconnected:
        v2vNic.upperLayerOut --> nl.in++;
        v2vNic.upperLayerIn <-- nl.out++;

        v2vNic.radioIn <-- v2vRadioIn;


}
