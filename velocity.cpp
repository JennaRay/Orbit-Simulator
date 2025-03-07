/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

 /*********************************************
  * VELOCITY : ADD
  *  v = v_0 + a t
  *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
	dx += acceleration.getDDX() * time;
	dy += acceleration.getDDY() * time;
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
	return sqrt(dx * dx + dy * dy);
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
	double radians = angle.getRadians(); // Get the angle in radians
	dx = magnitude * sin(radians);       // Compute dx using the cosine of the angle
	dy = magnitude * cos(radians);       // Compute dy using the sine of the angle
}
