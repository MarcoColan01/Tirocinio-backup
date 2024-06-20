#include "EventScheduler.h"
#include "math.h"

Define_Module(EventScheduler);

void EventScheduler::initialize(int stage) {
  cSimpleModule::initialize(stage);

  if (stage == INITSTAGE_LOCAL) {
    scheduleAt(simTime(), new cMessage("selfClean"));
  }
}

void EventScheduler::handleMessage(cMessage* msg) {
  simtime_t now = simTime();
  auto it = scheduled.begin();
  while (it != scheduled.end()) {
    if (*it < now){
      it = scheduled.erase(it);
      EV << "CANCELLATO" <<endl;
    }else
      ++it;
  }
  //scheduled.erase(
  //    std::remove_if(scheduled.begin(), scheduled.end(),
  //                   [&](const simtime_t& x) mutable { return x < now; }),
  //    scheduled.end());
  scheduleAt(now + 0.01, new cMessage("selfClean"));
  cancelAndDelete(msg);
}

simtime_t EventScheduler::getTime(simtime_t intended) {
  double increment = 0.000001; //uniform(0,0.00001); //0.00005; //1 ms
  double current = 0;
  for ( auto it = scheduled.begin(); it != scheduled.end(); it++ ){
    while((fabs((*it) - (intended + current)).dbl()) < increment)
      current+=increment;
  }
  scheduled.insert(intended + current);
  EV << "SCHEDULATO A: " << (intended + current) << endl;
  return intended + current;
}
