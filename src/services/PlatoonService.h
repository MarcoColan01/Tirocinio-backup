#ifndef _PLATOONSERVICE_H
#define _PLATOONSERVICE_H

#include "nodes/mec/MECPlatform/MECServices/MECServiceBase/MecServiceBase.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "modules/globalplatoonsmanager/GlobalPlatoonsManager.h"

using namespace std;
class PlatoonService : public MecServiceBase{
	private:
    	map<pair<string, string>, inet::TcpSocket*> mecAppSocket;
    	GlobalPlatoonsManager* platoonsManager;

    	simsignal_t platoonProcessingTimeSignal;

	public:
    	PlatoonService();

	protected:
    	virtual void initialize(int stage) override;
    	virtual void finish() override;
    	virtual void handleMessage(cMessage *msg) override;

    	virtual void handleGETRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket) override;
    	virtual void handlePOSTRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket)   override;
    	virtual void handlePUTRequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket)    override;
    	virtual void handleDELETERequest(const HttpRequestMessage *currentRequestMessageServed, inet::TcpSocket* socket) override;

    	void sendAcceleration(string platoonId, string dstCarId, string triggeringCar, double acceleration,double calcTime);

    	virtual ~PlatoonService();
};

#endif
