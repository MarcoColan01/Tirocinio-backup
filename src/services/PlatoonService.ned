package simulator_5g_v2x.services;

import simu5g.nodes.mec.MECPlatform.MECServices.MECServiceBase.IMECService;
import inet.applications.contract.IApp;

simple PlatoonService like IMECService, IApp
{
	parameters:
	    @signal[platoonProcessingTimeSignal](type="simtime_t");
	    @statistic[platoonProcessingTime](title="platoon processing time"; source="platoonProcessingTimeSignal"; record=vector,stats; interpolationmode=none);
		int requestQueueSize = default(0);
        int subscriptionQueueSize = default(0);
        string localAddress = default(""); // local address; may be left empty ("")
        int localPort = default(1000);     // localPort number to listen on
        string dataTransferMode @enum("bytecount","object","bytestream") = default("bytestream"); // bytestream for emulation
        double LocationSubscriptionPeriod @unit(s)= default(1s);
        
        bool loadGenerator = default(false);
    	double betaa  = default(0);  // used only if loadGenerator is true
    	int numBGApps = default(0); // used only if loadGenerator is true
        
        double requestServiceTime  @unit(s) = default(0.5us);
        double subscriptionServiceTime @unit(s) = default(0.5us);
        
        string serverThreadClass = default("simu5g.nodes.mec.MECPlatform.MECServices.MECServiceBase.SocketManager");
                
		string serviceName = default("PlatoonService");
       	string serviceVersion = default("v1");
       	string serviceSerialize = default("JSON");
       	
       	string transportId = default("LocAPI");
       	string transportName = default("LocAPI");
       	string transportType = default("REST_HTTP");
       	string transportProtocol = default("HTTP");
    
    	string catId = default("");
    	string catName = default("Platoon");
    	string catUri = default("");
    	string catVersion = default("v1");	
        
        string scopeOfLocality = default("MEC_HOST");
        bool consumedLocalOnly =  default(true);   
        
       	volatile double platoonProcessingTime @unit(s) = default(0s);
       	
        
        @display("i=block/app");
        
        //@signal[requestQueueSize];
        //@statistic[requestQueueSizeStat](title="Request queue size"; source="requestQueueSize"; record=mean,vector);
        @signal[responseTime];
        @statistic[responseTimeStat](title="Response time of foreground requests"; source="responseTime"; record=mean,vector);
	   
	gates:
		input socketIn @labels(TcpCommand/up);
		output socketOut @labels(TcpCommand/down);
}