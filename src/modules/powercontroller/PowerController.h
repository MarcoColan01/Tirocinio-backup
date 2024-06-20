#ifndef __POWERCONTROLLER_H_
#define __POWERCONTROLLER_H_

#include "inet/physicallayer/wireless/common/radio/packetlevel/Radio.h"
#include "math.h"
#include "omnetpp.h"

using namespace omnetpp;
using namespace inet;
using namespace physicallayer;
using namespace std;


/**
 * @brief Modulo per la gestione della potenza dell'antenna.
 * 
 */
class PowerController : public cSimpleModule, cListener {
  Radio *radio;
  double desiredReceivedPower;  // in dBm
  m coverDistance;

  void updateTxPower();

 public:
  /**
   * @brief Si setta la distanza che si desidera coprire. 
   * Questo metodo, basandosi sulla distanza ed il parametro di potenza ricevuta,
   * calcola e setta la nuova potenza di trasmissione.
   * 
   * @param distance 
   */
  void setCoverDistance(m distance);

  /**
   * @brief Listener per ricevere i segnali di trasmissione avviata e terminata.
   * Lo utilizziamo per disegnare durante la simulazione grafica il raggio di copertura
   * dell'antenna
   */
  virtual void receiveSignal(cComponent *source, simsignal_t signalID,
                             cObject *obj, cObject *details) override;

 protected:
  void initialize(int stage);
  virtual int numInitStages() const { return inet::NUM_INIT_STAGES; }
};
#endif
