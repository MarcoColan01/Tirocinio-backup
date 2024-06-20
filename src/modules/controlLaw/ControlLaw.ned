package simulator_5g_v2x.modules.controlLaw;

moduleinterface ControlLaw{
    @display("i=block/dispatch,,0");
}

simple CACCControlLaw like ControlLaw{

    parameters:
        @display("i=block/dispatch,,0");
    	@class("CACCControlLaw");
        double C1 = default(0.5);
        double csi = default(1);
        double omega_n @unit("Hz") = default(0.2Hz);
        double distance @unit("m") = default(20m);
}

simple PLOEGControlLaw like ControlLaw{

    parameters:
        @display("i=block/dispatch,,0");
    	@class("PLOEGControlLaw");
         double k_p = default(1.0);
       	 double k_d = default(1.0);
         //double k_dd = default(1.0);
         double h @unit("s") = default(0.5s);
}