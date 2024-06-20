import nodes.mec.MECPlatform.MECPackets;
import inet.applications.base.ApplicationPacket;

class VehicleControlPacket extends MECPacket{
	simtime_t creationTime;
  int sequenceNumber;
}

class VehicleStartPacket extends VehicleControlPacket{
    double vehicleLength;
    string carId;
    string sumoCarId;
    double position_x;
    double position_y;
    double position_z;
	double acceleration;
	double speed;
	double distance;
	string frontVehicle;
}

class VehicleStatusPacket extends VehicleControlPacket{
    //unsigned int carId;
    double position_x;
    double position_y;
    double position_z;
	double acceleration;
	double speed;
	double distance;
	string frontVehicle;
	double desiredAcceleration;
//  bool isOffline;
}

class VehicleInstructionPacket extends VehicleControlPacket{
  bool isLeader;
	double acceleration;
  double thisAoi;
  double precedingAoi;
  double leaderAoi;
  string triggeringCarId;
}

class VehiclePlatoonInfoPacket extends VehicleControlPacket{ 
	string platoonId;
	string platoonCarId;
}

class LowLevelPacket extends inet::ApplicationPacket{
    unsigned int carId;
    double position_x;
    double position_y;
    double position_z;
	double acceleration;
	double speed;
	double distance;
	string frontVehicle;
}