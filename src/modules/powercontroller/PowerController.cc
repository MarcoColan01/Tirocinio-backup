#include "PowerController.h"

#include "inet/common/Simsignals.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/FlatTransmitterBase.h"

using namespace math;

Define_Module(PowerController);

void PowerController::initialize(int stage) {
  if (stage == INITSTAGE_APPLICATION_LAYER) {
    desiredReceivedPower = par("desiredReceivedPower");
    coverDistance = m(par("coverDistance"));
    radio = check_and_cast<Radio *>(
        getParentModule()->getSubmodule(par("nicName"))->getSubmodule("radio"));
    radio->subscribe("transmissionStarted", this);
    radio->subscribe("transmissionEnded", this);
    //updateTxPower();
  }
}

void PowerController::updateTxPower() {
  FlatTransmitterBase *transmitter =
      check_and_cast<FlatTransmitterBase *>(radio->getSubmodule("transmitter"));
  Hz freq = transmitter->getCenterFrequency();
  mps propSpeed = radio->getMedium()->getPropagation()->getPropagationSpeed();

  W txPower = pW(1);
  if (coverDistance.get() > 0) {
    // siamo su antenna isotropica
    // computePathLoss calcola (lambda / (4 * pi * distance))^2
    // eleviamo alla -1 per invertire num e den
    // convertiamo in db
    double pathLossdB =
        (10 * log10(pow(radio->getMedium()->getPathLoss()->computePathLoss(
                            propSpeed, freq, coverDistance),
                        -1)));
    // se txPower è una variabile:
    // desiredReceivedPower = txPower - FSPL
    // txPower = desiredReceivedPower + FSPL
    double txPowerdBmW = pathLossdB + desiredReceivedPower;
    txPower = W(mW(dBmW2mW(txPowerdBmW)));
  }
  transmitter->setPower(txPower);
  EV << "PowerController::updateTxPower: txPower " << txPower
     << " radius: " << coverDistance
     << " received power at edge: " << desiredReceivedPower << endl;
}

void PowerController::setCoverDistance(m distance) {
  this->coverDistance = distance;
  updateTxPower();
}

void PowerController::receiveSignal(cComponent *source, simsignal_t signalID,
                                    cObject *obj, cObject *details) {
  if (signalID == transmissionStartedSignal) {
    FlatTransmitterBase *transmitter = check_and_cast<FlatTransmitterBase *>(
        radio->getSubmodule("transmitter"));

    W txPower = transmitter->getPower();
    double txPowerDBm = mW2dBmW(mW(txPower).get());
  double pathLoss = txPowerDBm + 85;  // sens receiver
    // 20log10(d_km) + 20log10(f_ghz) + 92.45 = pathLoss
    double f_db = 20 * log10(5.9);
    pathLoss = pathLoss - f_db - 92.45;
    double d_km = pow(10, pathLoss / 20);
    getParentModule()->getDisplayString().set(
        ("i=device/car,,0;is=vs;bgb=,,,,0;r=" + std::to_string(d_km * 1000) +
         ",#008000;")
            .c_str());
  } else if (signalID == transmissionEndedSignal) {
    getParentModule()->getDisplayString().set(
        "i=device/car,,0;is=vs;bgb=,,,,0;");
  }
}