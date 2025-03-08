#include <iostream>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "orbiter.h"
#include "physics.h"

using namespace std;

void Orbiter::move(double time)
{
	Angle objAngle(getDirectionOfGravityPull(position.getMetersX(), position.getMetersY()));
	Angle objAngleVelocity(getDirectionOfGravityPull(velocity.getDX(), velocity.getDY()));
	// Possibly need
	/*objAngleVelocity.reverse();*/
	objAngle.reverse();
	double secondsPerFrame = getTpf(getTd(24, 60), 30);
   //pretty sure we need to include update angle and something to do with the acceleration in here.

   // figure out acceleration
   double gn = getGravity(getHeightAboveEarth(position.getMetersX(), position.getMetersY()));
   double ddx = getHorizontalComponentOfAcceleration(gn, objAngle.getRadians());
   double ddy = getVerticalComponentOfAcceleration(gn, objAngle.getRadians());

   // figure out velocity
   double newV = findVelocity(velocity.getSpeed(), objAngleVelocity.getRadians(), secondsPerFrame);
   //horizontal and vertical components of velocity
   double dx = getHorizontalComponentOfAcceleration(newV, angle.getRadians());
   double dy = getVerticalComponentOfAcceleration(newV, angle.getRadians());
   velocity.setDX(dx);
   velocity.setDY(dy);

   // figure out position
   double x = getDistanceComponent(position.getMetersX(), velocity.getDX(), secondsPerFrame, ddx);
   double y = getDistanceComponent(position.getMetersY(), velocity.getDY(), secondsPerFrame, ddy);

   position.setMetersX(x);
   position.setMetersY(y);
 

   angle.add(0.02);
}