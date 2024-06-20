#ifndef MODULES_DEPENDENCYGRAPH_DEPENDENCYGRAPH_H_
#define MODULES_DEPENDENCYGRAPH_DEPENDENCYGRAPH_H_

#include <omnetpp.h>
#include <list>

using namespace std;
using namespace omnetpp;


class DependencyGraph: public cSimpleModule {
	public:

		virtual void addVehicle(string carId) = 0;
		virtual void removeVehicle(string carId) = 0;
		virtual list<string> getVehicleDependencies(string carId) = 0;
};

#endif
