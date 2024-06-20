package simulator_5g_v2x.modules.lowlevelcontroller;

simple LowLevelController
{
    parameters:
        @signal[accelerationSignal](type="double");
        @signal[distanceSignal](type="double");
        @signal[speedSignal](type="double");
        @signal[posXSignal](type="double");
        @signal[posYSignal](type="double");
        @signal[posZSignal](type="double");



        @statistic[acceleration](title="acceleration"; source="accelerationSignal"; record=vector,stats; interpolationmode=none);
        @statistic[distance](title="distance"; source="distanceSignal"; record=vector,stats; interpolationmode=none);
        @statistic[speed](title="speed"; source="speedSignal"; record=vector,stats; interpolationmode=none);
        @statistic[posX](title="position x"; source="posXSignal"; record=vector,stats; interpolationmode=none);
        @statistic[posY](title="position y"; source="posYSignal"; record=vector,stats; interpolationmode=none);
        @statistic[posZ](title="position z"; source="posZSignal"; record=vector,stats; interpolationmode=none);

        double updatePeriod @unit(s) = default(100ms);
        double betaAcceleration = default(0.2);
        double betaDeceleration = default(0.2);
        double expectedSpeed @unit(mps) = default(25mps);
        string speedPattern = default("follower");
        string speedPatternFile = default(""); // this is used only if speedPattern == "trace"
        //Used only if speedPattern == "trapezoid"
        double lowSpeed @unit(mps) = 16.7 mps;
        double lowSpeedDuration @unit(s) = 10s;
        double highSpeed @unit(mps) = 27.8 mps;
        double highSpeedDuration @unit(s) = 10s;
        double maxAccelaration = default(0.3); // m/s^2
        double maxDecelaration = default(1); // m/s^2

        double speedPatternStartTime @unit("s") = default(0s);  // when to start the pattern

        double speedOscillationAmplitude @unit(mps) = default(1.38mps); //about 5km/h
        double speedOscillationFreq @unit(Hz) = default(0.2Hz);

        string vehicleEngineFile = default("");
        string vehicleEngineType = default("first_order_lag");

        double interInstructionsMaxTime @unit(s) = default(1s);
        bool useActuationLag = default(true);
        bool hasSpeedPattern = default(false);

        @display("i=block/cogwheel");
}
