package simulator_5g_v2x.apps.main;
import inet.applications.contract.IApp;
//
// TODO auto-generated module
//
simple MainApp like IApp
{
        string mcastAddress;
        string v2vInterface;
        string mecAppName;
        int deviceAppPort;
        double startTime @unit("s") = default(1.1s);
        double statusUpdateInterval @unit("s") = default(0.1 s);
        string interfaceTableModule;
        string onboardControlLawMode @enum("synchronous", "asynchronous") = default("asynchronous");
        // Force modes are used for creating the training datasets
        string instructionMngMode @enum("auto", "cellularOnly", "cellularOnlyForced", "dsrcOnly" , "dsrcOnlyForced") = default("auto");
        // Hysterisis threshold to change RAT, used only with auto mode
        int instructionMngHysteresisThreshold = default(3); 
        
    gates:
        output socketOut;
        input socketIn;
}
