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
   //pretty sure we need to include update angle and something to do with the acceleration in here.

   // figure out acceleartion
   double gn = getGravity(position.getMetersY());
   double ddx = getHorizontalComponentOfAcceleration(gn, angle.getRadians());
   double ddy = getVerticalComponentOfAcceleration(gn, angle.getRadians());

   // figure out velocity
   double newV = findVelocity(velocity.getSpeed(), angle.getRadians(), time);
   //horizontal and vertical components of velocity
   double dx = getHorizontalComponentOfAcceleration(newV, angle.getRadians());
   double dy = getVerticalComponentOfAcceleration(newV, angle.getRadians());
   velocity.setDX(dx);
   velocity.setDY(dy);

   // figure out position
   double x = getDistanceComponent(position.getMetersX(), velocity.getDX(), time, ddx);
   double y = getDistanceComponent(position.getMetersY(), velocity.getDY(), time, ddy);

   position.setMetersX(x);
   position.setMetersY(y);

}