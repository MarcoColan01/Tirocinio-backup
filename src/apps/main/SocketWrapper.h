/*
 * SocketWrapper.h
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#include "inet/transportlayer/contract/udp/UdpSocket.h"

#ifndef APPS_MAIN_SOCKETWRAPPER_H_
#define APPS_MAIN_SOCKETWRAPPER_H_

using namespace inet;

/**
 * @brief Wrapper per le socket. Lo utilizziamo per dare un livello di 
 * astrazione in più, semplificando la gestione della socket.
 * In questo modo non dobbiamo passare agli handler socket, indirizzo e porta.
 * 
 */
class SocketWrapper {
  UdpSocket *socket;
  int port;
  L3Address address;

public:
  SocketWrapper(UdpSocket *socket, L3Address destAddress, int port);
  void send(Packet *packet);
  void setCallback(UdpSocket::ICallback *callback);
  friend class MainApp;
};

#endif /* APPS_MAIN_SOCKETWRAPPER_H_ */
