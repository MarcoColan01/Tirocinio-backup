#ifndef MODULES_CONTROLLAW_CONTROLLAW_H_
#define MODULES_CONTROLLAW_CONTROLLAW_H_

#include <omnetpp.h>
#include <list>
#include "VehiclesDataProvider.h"

using namespace std;
using namespace omnetpp;

class ControlLaw : public cSimpleModule {
	public:

		virtual list<double> computeLaw(list<string> toUpdate) = 0;
		virtual double computeLaw(string vehicleId) = 0;
		virtual double computeLawUsingSensorData(string physicalCarId) = 0;
		virtual list<int> getUsedPlatoonVehiclePositions(string vehicleId) = 0;
		virtual void setVehiclesDataProvider(VehiclesDataProvider* x) = 0;  //spostato qui
		virtual double getTargetDistance(vehicle_t data) = 0;
		virtual double getTargetDistance(status_t data) = 0;
};

#endif /* MODULES_CONTROLLAW_CONTROLLAW_H_ */
