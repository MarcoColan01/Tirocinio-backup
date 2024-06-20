#ifndef MODULES_DEPENDENCYGRAPH_LEADERFOLLOWERGRAPH_H_
#define MODULES_DEPENDENCYGRAPH_LEADERFOLLOWERGRAPH_H_

#include "modules/platooncontroller/PlatoonController.h"
#include "DependencyGraph.h"
#include <list>
#include <map>

using namespace std;
using namespace omnetpp;

class LeaderFollowerGraph: public DependencyGraph {
	public:
		LeaderFollowerGraph();
		virtual ~LeaderFollowerGraph();

		void addVehicle(string carId) override;
		void removeVehicle(string carId) override;
		list<string> getVehicleDependencies(string carId) override;

	protected:
		void initialize() override;

	private:
		map<string, list<string>> graph;
		PlatoonController *controller;
};

#endif /* MODULES_DEPENDENCYGRAPH_LEADERFOLLOWERGRAPH_H_ */
