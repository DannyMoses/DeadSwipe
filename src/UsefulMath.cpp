/*
 * UsefulMath.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: Robotics
 */

#include "UsefulMath.h"
#include "DeadSwipe.h"
#include <math.h>

// the sigmoid control loops used to make sure a motor reaches its
// target without over/undershooting
// o(e) = ((e / (m + |e|)) + f) * s where
// e is the error(distance from the target)
// m is the slope modifier
// f is the feedforward value
// s is the max speed of the motor
float sigmoid(float e,float m,float f,float s)
{
	float output = 0.0;
	if ( e > 0) {
		output = ((e/ m + abs(e)) + f) * s;
	} else if (e < 0) {
		output = ((e/ m + abs(e)) - f) * s;
	} else {
		output = 0.0;
	}

	if (output > 1.0) {
		return 1;
	} else if (output < -1.0) {
		return -1.0;
	} else {
		return output;
	}
}

// our DPP fix for the elevator
// where x is the number of revolutions
// and the function returns the distance per pulse
// C = 2pi(r+xt) where r is the radius, x is the # of revolutions and t is
// the thickness of the belt
// DPP = C/ GR * PPR where C circumference, GR is the gear ratio, and PPR is
// the pulses per revolution

float EncoderMagic(float x)
{
	float C = (2 *PI) * (RADIUS + (x * THICKNESS));


	return C / ELEVATOR_GEAR_RATIO * OPTICAL_PPR;
}

float scaleyFunction(float JoyRaw, int steepyness ){
//	JoyRaw     = Raw Joystick value
//	c	   = Some constant or whatever who cares
//      steepyness = How quickly the scaled value increases. smaller steepyness = faster increase



	if(steepyness % 2 == 0){
		return -2;
	} else {
		// float *scaledJoy = (JoyRaw^(1/steepyness));
		float scaledJoy = pow(JoyRaw, 1/steepyness);

		return scaledJoy;
	}
}





