/*
 * UsefulMath.h
 *
 *  Created on: Oct 20, 2015
 *      Author: Robotics
 */

#include "WPILib.h"
#include "DeadSwipe.h"

#ifndef SRC_USEFULMATH_H_
#define SRC_USEFULMATH_H_

#define RADIUS 1.3
#define THICKNESS 1/32
#define OPTICAL_PPR 500

// ~26 in  or 25.5
// -11 in off the ground
// 2 3/4 int form the wheels
// 1.3 in w/o windage
// 1.5 in at start
// 2 in at end
// 22.5 at highest
float sigmoid(float e,float m,float f,float s);
float EncoderMagic(float x);
float scaleyFunction(float JoyRaw, int steepyness );



#endif /* SRC_USEFULMATH_H_ */
