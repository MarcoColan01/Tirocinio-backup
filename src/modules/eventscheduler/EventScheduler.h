#ifndef _EVENTQUEUE_H_
#define _EVENTQUEUE_H_

#include "apps/packets/VehicleControlPacket_m.h"
#include "math.h"
#include "omnetpp.h"

using namespace omnetpp;
using namespace inet;
using namespace std;

class EventScheduler: public cSimpleModule {
  set<simtime_t> scheduled;

 public:
  EventScheduler(){};
  ~EventScheduler(){};
  simtime_t getTime(simtime_t intended);

 protected:
  void initialize(int stage);
  virtual int numInitStages() const { return inet::NUM_INIT_STAGES; }
  virtual void handleMessage(cMessage* msg);

};
#endif
