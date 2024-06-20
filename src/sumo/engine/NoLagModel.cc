/*
 * NoLagModel.cc
 *
 *  Created on: Oct 12, 2022
 *      Author: christian
 */

#include "NoLagModel.h"


double NoLagModel::getRealAcceleration(double speed_mps, double accel_mps2, double reqAccel_mps2, double timeStep){
    return reqAccel_mps2;
}


