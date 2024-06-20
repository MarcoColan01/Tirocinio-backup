
#include "veins/modules/mobility/traci/TraCIBuffer.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"
#include "veins/modules/mobility/traci/TraCIConnection.h"
#include "veins/modules/mobility/traci/TraCIConstants.h"
#include "veins_inet/VeinsInetMobility.h"

namespace veins {
  using namespace veins::TraCIConstants;

  /**
   * @brief Veicolo con la funzione per ottenere la distanza dal veicolo 
   * precedente mediante TraCI
   * 
   */
  class ExtendedVehicle : public veins::TraCICommandInterface::Vehicle {
    public:
      ExtendedVehicle(veins::TraCICommandInterface::Vehicle&& e)
          : veins::TraCICommandInterface::Vehicle(e) {}
      
      std::pair<std::string, double> getFollower(const double distance);
      bool checkCollision();
      void setLaneChangeMode(int32_t bitset);
      void setMinGap(double minGap);
      void setAcceleration(double acc, double t);
  };

  /**
   * Modulo che estende VeinsInetMobility
   * 
   */
  class ExtendedVeinsInetMobility : public VeinsInetMobility {
    public:
      /**
       * 
       * @return TraCICommandInterface::Vehicle* un'istanza di ExtendedVehicle
       */
      TraCICommandInterface::Vehicle* getVehicleCommandInterface() const override;

  };

}  // namespace veins
