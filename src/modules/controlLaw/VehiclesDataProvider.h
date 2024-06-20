#ifndef MODULES_CONTROLLAW_CARSPOSITIONPROVIDER_H_
#define MODULES_CONTROLLAW_CARSPOSITIONPROVIDER_H_

#include "common/types_t.h"
using namespace std;

/**
 * @brief Interfaccia provider di dati per il modulo ControlLaw.
 * Per non definire più implementazioni di legge di controllo (Lato MEC V2N e lato veicolo V2V)
 * Utilizziamo all'interno di controlaw questa interfaccia in modo da poter adattare il modulo
 * A diverse fonti di dati
 * 
 * SelfVehiclesDataProvider è il provider di dati quando il modulo ControlLaw viene usato
 * all'interno del veicolo.
 * 
 * Quando ControlLaw viene usato lato MEC, 
 * la classe PlatoonController implementa questa interfaccia per fornirle i dati
 */
class VehiclesDataProvider {
 public:
  virtual vehicle_t getVehicleByPosition(int position) = 0;
  virtual int getPositionByCarId(string carId) = 0;
  virtual bool exists(int position) = 0;
};

#endif
