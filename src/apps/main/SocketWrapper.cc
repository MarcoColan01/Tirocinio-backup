/*
 * SocketWrapper.cpp
 *
 *  Created on: Jul 17, 2022
 *      Author: nikolamarku
 */

#include "apps/main/SocketWrapper.h"

SocketWrapper::SocketWrapper(UdpSocket *socket, L3Address address, int port) {
  this->socket = socket;
  this->address = address;
  this->port = port;
  ASSERT(this->socket);
}

void SocketWrapper::send(Packet *packet) {
  if (socket->isOpen()) socket->sendTo(packet, address, port);
}

void SocketWrapper::setCallback(UdpSocket::ICallback *callback) {
  socket->setCallback(callback);
}

