//
// Copyright (C) 2009 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


#ifndef __SIMULATOR_5G_V2X_MULTINICHOSTAUTOCONFIGURATOR_H_
#define __SIMULATOR_5G_V2X_MULTINICHOSTAUTOCONFIGURATOR_H_

#include <omnetpp.h>
#include "inet/networklayer/configurator/ipv4/HostAutoConfigurator.h"
using namespace omnetpp;
using namespace inet;


class  MultiNicHostAutoConfigurator : public HostAutoConfigurator
{
  protected:
    virtual void setupNetworkLayer() override;
};


#endif
