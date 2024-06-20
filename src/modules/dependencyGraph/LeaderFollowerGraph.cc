#include "LeaderFollowerGraph.h"

Define_Module(LeaderFollowerGraph);

LeaderFollowerGraph::LeaderFollowerGraph() {
}

LeaderFollowerGraph::~LeaderFollowerGraph() {
}

void LeaderFollowerGraph::addVehicle(string carId) {
	EV << "LeaderFollowerGraph::addVehicle --- Adding to graph carId: " << carId << endl;
	list<string> newVehicleList;// = new list<string>();
	int carPos = controller->getPositionByCarId(carId);
	EV << "car pos: " << carPos<< endl;
	if(carPos > 0){
		newVehicleList.push_back(carId);										//Add new carId to its own car's list
		graph.at(controller->getCarIdByPosition(carPos - 1)).push_back(carId);	//Add new carId to preceding car's list
	}
	if(carPos > 1)
		graph.at(controller->getCarIdByPosition(0)).push_back(carId);			//Add new carId to leader car's list

	pair<std::map<string,list<string>>::iterator,bool> ret;
	ret = graph.insert(pair<string, list<string>>(carId, newVehicleList));

}

list<string> LeaderFollowerGraph::getVehicleDependencies(string carId) {
    Enter_Method("getVehicleDependencies");
	EV << "LeaderFollowerGraph::getVehicleDependencies --- For carId: " << carId << endl;
	EV << "Graph size: " << graph.size() << endl;
	for (auto& x: graph) {
	    EV << "Vehicle: " << x.first << " List size: " << x.second.size() << " elements: ";
	    for (auto &e : x.second)
	        EV << " "<<  e;
	    EV << endl;
	}
	return graph.at(carId);
}

void LeaderFollowerGraph::removeVehicle(string carId) {
}

void LeaderFollowerGraph::initialize() {
	EV << "LeaderFollowerGraph::initialize" << endl;
	controller = check_and_cast<PlatoonController *>(getParentModule()->getSubmodule("platoonController"));
}
