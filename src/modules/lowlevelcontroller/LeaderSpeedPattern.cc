#include "LeaderSpeedPattern.h"


// FACTORY METHOD
LeaderSpeedPattern* createLeaderSpeedPattern(cModule *lowLevelCtlMod){
    auto leaderPatternType = lowLevelCtlMod->par("speedPattern").stdstringValue();
    if (leaderPatternType.compare("constant")==0){
        return new ConstantLeaderSpeedPattern(lowLevelCtlMod);
    }
    if (leaderPatternType.compare("sinusoidal")==0){
        return new SinusoidalLeaderSpeedPattern(lowLevelCtlMod);
    }
    if (leaderPatternType.compare("trace")==0){
        return new TraceLeaderSpeedPattern(lowLevelCtlMod);
    }
    if (leaderPatternType.compare("trapezoid")==0){
        return new TrapezoidLeaderSpeedPattern(lowLevelCtlMod);
    }
    if (leaderPatternType.compare("free")==0){
        return new FreeLeaderSpeedPattern(lowLevelCtlMod);
    }

    // UNKNOWN
    return new LeaderSpeedPattern(lowLevelCtlMod);
}
