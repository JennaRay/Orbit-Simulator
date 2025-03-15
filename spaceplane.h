#pragma once

#include "orbiter.h"
#include "velocity.h"
#include "position.h"
#include "angle.h"
#include "uiDraw.h"
#include <cmath>


#define ROTATION_AMOUNT 0.1
#define THRUST_ACCEL 200000.0
#define TIME_STEP 1

using namespace std;



class SpacePlane : public Orbiter
{
public:
   SpacePlane() : Orbiter()
   {
      Position pos;
      pos.setPixelsX(-450);
      pos.setPixelsY(450);
      Velocity v(0.0, -2000);
      setPosition(pos);
      setVelocity(v);

      thrust = 0.0;
   }

   void draw(ogstream& gout)
   {
      gout.drawShip(getPosition(), getSpin(), thrust);
   }

   void rotate(double delta)
   {
      addSpin(delta);
   }
   void applyThrust()
   {
      thrust = THRUST_ACCEL;      
   }
   void stopThrust()
   {
      thrust = 0.0;
   }
   void moveForward()
   {
      double a = getSpin();
      double ax = thrust * sin(a);
      double ay = thrust * cos(a);


      Velocity v = getVelocity();
      v.setDX(v.getDX() + ax * TIME_STEP);
      v.setDY(v.getDY() + ay * TIME_STEP);

      Position pos = getPosition();
      double newX = pos.getMetersX() + v.getDX() * TIME_STEP + 0.5 * thrust * pow(TIME_STEP, 2);
      double newY = pos.getMetersY() + v.getDY() * TIME_STEP + 0.5 * thrust * pow(TIME_STEP, 2);

      setPosition(newX, newY);
      //cout << getPosition().getMetersX() << endl;
      //cout << getPosition().getMetersY() << endl;
   }
private:
   double thrust;
};
