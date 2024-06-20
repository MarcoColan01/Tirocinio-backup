cplusplus{{
    typedef std::list<std::pair<std::string, double>> PlatoonResponse;
}};
class PlatoonResponse {@existingClass;}

message ProcessResponseSelfMessage {
    string platoonId;
	string triggeringCarId;
    double calcTime;
	PlatoonResponse resp;
}
