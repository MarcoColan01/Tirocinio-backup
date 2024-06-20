/*
 * Handler.h
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#include "modules/lowlevelcontroller/LowLevelController.h"
#include "InstructionManager.h"

#ifndef APPS_MAIN_HANDLER_H_
#define APPS_MAIN_HANDLER_H_

#include "SocketWrapper.h"

using namespace std;


typedef struct vehicle_instruction_t{
    bool isLeader;
    double accelaration;
} vehicle_instruction_t;


enum OnboardControlLawMode {
    SYNCHRONOUS,
    ASYNCHRONOUS
};

/**
 * @brief Interfaccia di gestione delle comunicazioni tra veicolo e target (MEC nel caso V2N, 802.11p nel caso V2V)
 * All'handler viene delegata tutta la gestione delle comunicazioni e del calcolo/ricezione di nuove istruzioni da attuare.
 * Gli vengono forniti i dati del veicolo da dover comunicare e gli si imposta un callback per ottenere le informazioni o
 * istruzioni nuove.
 * 
 */
class Handler {

public:

  /**
   * @brief Interfaccia di callback del gestore dell'Handler
   * 
   */
  class OnNewVehiclePacketListener {
  public:
    /**
     * @brief Metodo chiamato dall'handler dopo aver ricevuto l'id del platoon e del veicolo
     * 
     * NB: Questo metodo viene chiamato solo dall'handler di gestione V2N (MEC) 
     * 
     * @param handler chiamante
     * @param platoonInfo id del platoon e del veicolo
     */
    virtual void onPlatoonInfoReceived(Handler *handler, const VehiclePlatoonInfoPacket *platoonInfo) = 0;
    
    /**
     * @brief Metodo chiamato dall'handler dopo aver calcolato/ricevuto l'istruzione di accelerazione/decelarazione
     * 
     * @param handler chiamante
     * @param instruction istruzione del veicolo
     */
    virtual void onNewInstructionReceived(Handler *handler, const VehicleInstructionPacket *instruction) = 0;

    /**
        * @brief Metodo chiamato dall'handler dopo aver calcolato/ricevuto l'istruzione di accelerazione/decelarazione
        *
        * @param handler chiamante
        * @param instruction istruzione del veicolo
        */
    virtual void onNewInstructionReceived(Handler *handler, const vehicle_instruction_t instruction) = 0;
  };

  /**
   * @brief Nome dell'handler
   * 
   * @return const char* 
   */
  virtual const char* getName() = 0;
  
  /**
   * @brief Inizializzazione dell'handler. L'handler memorizza il/i socket necessari
   * dal pool di socket disponibili
   * 
   * @param sockets mappa delle socket disponibili.
   */
  virtual void init(map<int, SocketWrapper*> sockets) = 0;
  /**
   * @brief Controllo se l'handler è pronto a ricevere dati
   * 
   * @return true 
   * @return false 
   */
  virtual bool isReady() = 0;

  /**
   * @brief Metodo per fornire nuovi dati all'handler
   * 
   * @param carStatus dati del veicolo
   */
  virtual void onNewDataArrived(status_t carStatus) = 0;

  /**
   * @brief Set del callback che l'handler chiamerà quando avrà a disposizione nuove istruzioni o info del platoon
   * 
   * @param listener callback
   */
  virtual void setOnNewVehiclePacketListener(OnNewVehiclePacketListener *listener) {
    this->onNewVehiclePacketListener = listener;
  }


  /**
   * @brief Set instruction to Instruction Manager. Each handler knows which instruction to update
   *
   * @param instractionMng
   * @param instruction
   */
  virtual void updateInstructionManager(InstructionManager* instructionMng, double instruction) = 0;

//  /**
//   * @brief Frequenza di aggiornamento dell'handler.
//   *
//   * @return double in secondi
//   */
// virtual double getUpdateDelay() = 0;

protected:
  OnNewVehiclePacketListener *onNewVehiclePacketListener = nullptr;
};

#endif /* APPS_MAIN_HANDLER_H_ */
