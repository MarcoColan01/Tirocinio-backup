#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>


#include "omnetpp.h"

using namespace omnetpp;
using namespace std;

class LeaderSpeedPattern{

public:
    LeaderSpeedPattern(cModule  *lowLevelCtlMod){
        this->lowLevelCtlMod = lowLevelCtlMod;
        initialSpeed = this->lowLevelCtlMod->par("expectedSpeed").doubleValue();
        timeStepInterval = this->lowLevelCtlMod->findModuleByPath("<root>.veinsManager")->par("updateInterval").doubleValue();

    }

    double getSpeed(double simtime, double currentSpeed){
        return hasStarted ? computeNewSpeed(simtime, currentSpeed) :  initialSpeed;
    }

    virtual void startPattern(double simtime){
        startSimtime = simtime;
        hasStarted = true;
    }

    virtual bool useActuationLag(bool currentValue){
        return currentValue;
    }

protected:
    virtual double computeNewSpeed(double simtime, double currentSpeed){
        return currentSpeed; //-1; //it means no speed to set, let SUMO use its own speed models
    }

    cModule *lowLevelCtlMod;
    bool hasStarted = false;
    double initialSpeed;
    double startSimtime = 0;
    double timeStepInterval;
};

class FreeLeaderSpeedPattern: public LeaderSpeedPattern{
public:
    FreeLeaderSpeedPattern(cModule *lowLevelCtlMod): LeaderSpeedPattern(lowLevelCtlMod){}

protected:
    virtual double computeNewSpeed(double simtime, double currentSpeed) override {
        return -1; //it means no speed to set, let SUMO use its own speed models
    }

};


class ConstantLeaderSpeedPattern: public LeaderSpeedPattern {
public:
    ConstantLeaderSpeedPattern(cModule *lowLevelCtlMod): LeaderSpeedPattern(lowLevelCtlMod) {
        speed = this->lowLevelCtlMod->par("expectedSpeed").doubleValue();
    }
protected:
    virtual double computeNewSpeed(double simtime, double currentSpeed) override {
        return speed;
    }
private:
    double speed;
};


class SinusoidalLeaderSpeedPattern: public LeaderSpeedPattern {
public:
    SinusoidalLeaderSpeedPattern(cModule *lowLevelCtlMod): LeaderSpeedPattern(lowLevelCtlMod) {
        meanSpeed = this->lowLevelCtlMod->par("expectedSpeed").doubleValue();
        speedOscillationAmplitude = this->lowLevelCtlMod->par("speedOscillationAmplitude").doubleValue();
        speedOscillationFreq = this->lowLevelCtlMod->par("speedOscillationFreq").doubleValue();
    }

protected:
    virtual double computeNewSpeed(double simtime, double currentSpeed) override {
        return meanSpeed + speedOscillationAmplitude* sin(2*M_PI * (simtime- startSimtime) * speedOscillationFreq);
    }

private:
    double meanSpeed;
    double speedOscillationAmplitude;
    double speedOscillationFreq;
};



class TraceLeaderSpeedPattern: public LeaderSpeedPattern {
public:
    TraceLeaderSpeedPattern(cModule *lowLevelCtlMod): LeaderSpeedPattern(lowLevelCtlMod){
        auto traceFile = this->lowLevelCtlMod->par("speedPatternFile").stdstringValue();
        prepareTraceFromFile(traceFile);
    }
    virtual bool useActuationLag(bool currentValue) override {
        return false;
    }

protected:
    virtual double computeNewSpeed(double simtime, double currentSpeed) override {
        if (speedTrace.empty())
            return currentSpeed; // keep the current speed because the trace is finished
        auto nextSpeed = speedTrace.front()[1];
        speedTrace.pop_front();

        return nextSpeed;
    }

private:
    list<vector<double>> speedTrace;

    void prepareTraceFromFile(string filename){
        vector<double> row;
        string line, word;

        fstream file (filename, ios::in);
        if(file.is_open())
        {
            while(getline(file, line))
            {
                row.clear();
                stringstream str(line);
                while(getline(str, word, ','))
                    row.push_back(stod(word));
                speedTrace.push_back(row);
            }
        }
    }


};




class TrapezoidLeaderSpeedPattern : public LeaderSpeedPattern{
protected:
    class State{
    public:
        TrapezoidLeaderSpeedPattern *speedPattern;
        double startTime;

        State(TrapezoidLeaderSpeedPattern *speedPattern){
            this->speedPattern = speedPattern;
        };

        void setStartTime(double startTime){
            this->startTime = startTime;
        }

        virtual double getSpeed(double simtime, double currentSpeed) = 0;
    };

    class LowSpeedState : public State{
    public:
        LowSpeedState(TrapezoidLeaderSpeedPattern *speedPattern): State(speedPattern){}

        virtual double getSpeed(double simtime, double currentSpeed) override {
            if (simtime - startTime >= speedPattern->lowSpeedDuration){
                speedPattern->changeState(speedPattern->low2HighSpeedState);
            }
            return speedPattern->lowSpeed;
        }
    };

    class HighSpeedState : public State{
    public:
        HighSpeedState(TrapezoidLeaderSpeedPattern *speedPattern): State(speedPattern){}
        virtual double getSpeed(double simtime, double currentSpeed) override {
            if (simtime - startTime >= speedPattern->highSpeedDuration){
                speedPattern->changeState(speedPattern->high2LowSpeedState);
            }
            return speedPattern->highSpeed;
        }
    };

    class Low2HighSpeedState : public State{
    public:
        Low2HighSpeedState(TrapezoidLeaderSpeedPattern *speedPattern): State(speedPattern){}
        virtual double getSpeed(double simtime, double currentSpeed) override {
            if (currentSpeed >= speedPattern->highSpeed){
                speedPattern->changeState(speedPattern->highSpeedState);
                return currentSpeed;
            }
            return currentSpeed + speedPattern->maxAccelaration * speedPattern->timeStepInterval;
        }

    };
    class High2LowSpeedState : public State{
    public:
        High2LowSpeedState(TrapezoidLeaderSpeedPattern *speedPattern): State(speedPattern){}
        virtual double getSpeed(double simtime, double currentSpeed) override {
            if (currentSpeed <= speedPattern->lowSpeed){
                speedPattern->changeState(speedPattern->lowSpeedState);
                return currentSpeed;
            }
            return currentSpeed - speedPattern->maxDecelaration * speedPattern->timeStepInterval;
        }
    };

    State *activeState = nullptr;
    LowSpeedState *lowSpeedState = nullptr;
    HighSpeedState *highSpeedState = nullptr;
    Low2HighSpeedState *low2HighSpeedState = nullptr;
    High2LowSpeedState *high2LowSpeedState = nullptr;

    double lowSpeed;
    double highSpeed;
    double lowSpeedDuration;
    double highSpeedDuration;
    double maxAccelaration;
    double maxDecelaration;
    //    double timestepFactor = 1.0;

    public:
    TrapezoidLeaderSpeedPattern(cModule *lowLevelCtlMod): LeaderSpeedPattern(lowLevelCtlMod){
        lowSpeed = this->lowLevelCtlMod->par("lowSpeed").doubleValue();
        highSpeed = this->lowLevelCtlMod->par("highSpeed").doubleValue();
        lowSpeedDuration = this->lowLevelCtlMod->par("lowSpeedDuration").doubleValue();
        highSpeedDuration = this->lowLevelCtlMod->par("highSpeedDuration").doubleValue();
        maxAccelaration = this->lowLevelCtlMod->par("maxAccelaration").doubleValue();
        maxDecelaration = this->lowLevelCtlMod->par("maxDecelaration").doubleValue();

        if (this->lowLevelCtlMod->par("useActuationLag").boolValue()){
            //This is necessary because actuation lag expects m/s^2
            timeStepInterval *= 1.0/timeStepInterval;
        }

        //create speed states
        lowSpeedState = new LowSpeedState(this);
        highSpeedState = new HighSpeedState(this);
        low2HighSpeedState = new Low2HighSpeedState(this);
        high2LowSpeedState = new High2LowSpeedState(this);

    }

    //    virtual bool useActuationLag(bool currentValue) override {
    //        return false;
    //    }

    protected:
    virtual void startPattern(double simtime){
        LeaderSpeedPattern::startPattern(simtime);
        activeState = lowSpeedState;
    }

    virtual double computeNewSpeed(double simtime, double currentSpeed) override {
        return activeState->getSpeed(simtime, currentSpeed);
    }

    void changeState(State *newState){
//        delete activeState;
        activeState = newState;
        activeState->setStartTime(simTime().dbl());
    }

};


// FACTORY METHOD
LeaderSpeedPattern* createLeaderSpeedPattern(cModule *lowLevelCtlMod);



