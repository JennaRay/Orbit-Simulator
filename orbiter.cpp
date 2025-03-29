#include <iostream>
#include "orbiter.h"
#include "physics.h"

using namespace std;

/****************************************
 * ORBITER::MOVE
 * Move the orbiter based on the current velocity and acceleration
 *****************************************/

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

/****************************************
 * ORBITER::COLLIDE
 * set the orbiter to collided (to be overwritten)
 *****************************************/
void Orbiter::collide()
{
   isCollided = true;
}

//Fragment class

void Fragment::kick()
{
   //random angle between 0 and 360
   Angle newAngle(random(-180, 180));
   setAngle(newAngle);
   //add random velocity to speed between 5000 and 9000 m/s
   double newSpeed = random(5000, 9000);
   Velocity v = getVelocity();
   v.addDX(newSpeed);
   v.addDY(newSpeed);
   setVelocity(v);
      //update position
   double newX = getDistance(getPosition().getPixelsX(), v.getDX(), 0.004, 0.0);
   double newY = getDistance(getPosition().getPixelsY(), v.getDY(), 0.004, 90.0);
   setPositionPixels(newX, newY);
}
