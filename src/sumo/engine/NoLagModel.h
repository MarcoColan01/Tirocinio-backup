/*
 * NoLagModel.cc
 *
 *  Created on: Oct 12, 2022
 *      Author: christian
 */

#include "GenericEngineModel.h"


class NoLagModel : public GenericEngineModel{

public:

    virtual double getRealAcceleration(double speed_mps, double accel_mps2, double reqAccel_mps2, double timeStep = 0);

    virtual void setParameter(const std::string parameter, const std::string& value) {};
    virtual void setParameter(const std::string parameter, double value){};
    virtual void setParameter(const std::string parameter, int value){};

};

