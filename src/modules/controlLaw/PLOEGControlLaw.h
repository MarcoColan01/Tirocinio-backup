#ifndef MODULES_CONTROLLAW_PLOEGCONTROLLAW_H_
#define MODULES_CONTROLLAW_PLOEGCONTROLLAW_H_

#include "ControlLaw.h"
#include "modules/platooncontroller/PlatoonController.h"

class PLOEGControlLaw : public ControlLaw {
    public:
        PLOEGControlLaw();
        virtual ~PLOEGControlLaw();
        list<double> computeLaw(list<string> toUpdate) override;
        double computeLaw(string vehicleId) override;

        double computeLawUsingSensorData(string physicalCarId) override;
        void setVehiclesDataProvider(VehiclesDataProvider* x) override{
            this -> vehiclesDataProvider = x;
        }

        list<int> getUsedPlatoonVehiclePositions(string platoonCarId) override;
        double getTargetDistance(vehicle_t data) override;
        double getTargetDistance(status_t data) override;

        protected:
            virtual void initialize() override;
            double computePerVehicle(string carId);
        private:
            //Nuovi parametri
            double k_p;
            double k_d;
            //double k_dd;
            double headwayDistance;

            VehiclesDataProvider* vehiclesDataProvider;

            double computePLOEGControlLaw(vehicle_t v, vehicle_t front);
            //double computeCACCControlLaw(vehicle_t v, vehicle_t front, vehicle_t leader);

};

#endif
