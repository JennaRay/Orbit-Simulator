#include <iostream>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "orbiter.h"
#include "physics.h"

using namespace std;

//old move function
//void Orbiter::move(double time)
//{
//	Angle objAngle(getDirectionOfGravityPull(position.getMetersX(), position.getMetersY(), orbitCenter.getMetersX(), orbitCenter.getMetersY()));
//	//Angle objAngleVelocity(getDirectionOfGravityPull(velocity.getDX(), velocity.getDY()));
//	// Possibly need
//	/*objAngleVelocity.reverse();*/
//	objAngle.reverse();
//	double secondsPerFrame = getTpf(getTd(24, 60), 30);
//   //pretty sure we need to include update angle and something to do with the acceleration in here.
//
//   // figure out acceleration
//   double gn = getGravity(getHeightAboveEarth(position.getMetersX(), position.getMetersY()));
//   double ddx = getHorizontalComponentOfAcceleration(gn, objAngle.getRadians());
//   double ddy = getVerticalComponentOfAcceleration(gn, objAngle.getRadians());
//
//   // figure out velocity
//   double newV = findVelocity(velocity.getSpeed(), gn, secondsPerFrame);
//   ////horizontal and vertical components of velocity
//   double dx = getHorizontalComponentOfAcceleration(newV, angle.getRadians());
//   double dy = getVerticalComponentOfAcceleration(newV, angle.getRadians());
//
//   velocity.setDX(dx);
//   velocity.setDY(dy);
//
//   // figure out position
//   double x = getDistanceComponent(position.getMetersX(), velocity.getDX(), secondsPerFrame, ddx);
//   double y = getDistanceComponent(position.getMetersY(), velocity.getDY(), secondsPerFrame, ddy);
//
//
//   position.setMetersX(x);
//   position.setMetersY(y);
// 
//   angle.add(0.02);
//   //spin+= 0.03;
//}

//new move function because it was easier to just rewrite
void Orbiter::move(double time)
{
   //get time
   double secondsPerFrame = getTpf(getTd(24, 60), 30);

   //gind angle of pull of gravity
   Angle aGravity;
   aGravity.setRadians(getDirectionOfGravityPull(position.getMetersX(), position.getMetersY(), orbitCenter.getMetersX(), orbitCenter.getMetersY()));
   //find acceleration of gravity
   double gravity = getGravity(getHeightAboveEarth(position.getMetersX(), position.getMetersY()));
   double ddx = getHorizontalComponentOfAcceleration(gravity, aGravity.getRadians());
   double ddy = getVerticalComponentOfAcceleration(gravity, aGravity.getRadians());

   //find new position
   double x = position.getMetersX() + velocity.getDX() * secondsPerFrame + 0.5 * ddx * pow(secondsPerFrame, 2);
   double y = position.getMetersY() + velocity.getDY() * secondsPerFrame + 0.5 * ddy * pow(secondsPerFrame, 2);

   //set new position
   position.setMetersX(x);
   position.setMetersY(y);

   //update velocity
   double newV = velocity.getSpeed() + gravity * secondsPerFrame;
   double dx = velocity.getDX() + ddx * secondsPerFrame;
   double dy = velocity.getDY() + ddy * secondsPerFrame;

   //set velocity
   velocity.setDX(dx);
   velocity.setDY(dy);

   //update angle
   double angularVelocity = (atan2(0 - dx, 0 - dy));
   angle.add(angularVelocity);
   if (angularVelocity > 0)
      spin += angularVelocity * -0.01;
   else
      spin += angularVelocity * 0.01;
}