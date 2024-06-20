#ifndef MODULES_CONTROLLAW_CACCCONTROLLAW_H_
#define MODULES_CONTROLLAW_CACCCONTROLLAW_H_

#include "ControlLaw.h"
#include "modules/platooncontroller/PlatoonController.h"

class CACCControlLaw : public ControlLaw {
 public:
  CACCControlLaw();
  virtual ~CACCControlLaw();
  list<double> computeLaw(list<string> toUpdate) override;
  double computeLaw(string vehicleId) override;

  double computeLawUsingSensorData(string physicalCarId) override;
  void setVehiclesDataProvider(VehiclesDataProvider* x) override{
    this->vehiclesDataProvider = x;
  }

  list<int> getUsedPlatoonVehiclePositions(string platoonCarId) override;
  double getTargetDistance(vehicle_t data) override;
  double getTargetDistance(status_t data) override;

 protected:
  virtual void initialize() override;
  double computePerVehicle(string carId);

 private:
  double c1, csi, omega_n, targetDistance;
  double alpha1, alpha2, alpha3, alpha4, alpha5;
  VehiclesDataProvider* vehiclesDataProvider;

  double computeCACCControlLaw(vehicle_t v, vehicle_t front, vehicle_t leader);
};

#endif /* MODULES_CONTROLLAW_CACCCONTROLLAW_H_ */
