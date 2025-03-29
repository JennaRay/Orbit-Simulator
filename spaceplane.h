#pragma once

#include "orbiter.h"
#include "velocity.h"
#include "position.h"
#include "angle.h"
#include "uiDraw.h"
#include "bullet.h"
#include <cmath>
#include <vector> // to store bullets


#define ROTATION_AMOUNT 0.1
#define THRUST_ACCEL 200000.0
#define TIME_STEP 1

using namespace std;

class TestSpacePlane;

class SpacePlane : public Orbiter
{
public:
   friend TestSpacePlane;

   //Constructors
   SpacePlane() : Orbiter()
   {
      Position pos;
      pos.setPixelsX(-450);
      pos.setPixelsY(450);
      Velocity v(0.0, -2000);
      setPosition(pos);
      setVelocity(v);
      setRadius(10); // radius in pixels
      thrust = 0.0;
   }

   void draw(ogstream& gout) { gout.drawShip(getPosition(), getSpin(), thrust);}
   void rotate(double delta)   { addSpin(delta);   }
   void applyThrust()   { thrust = THRUST_ACCEL;   }
   void stopThrust()   { thrust = 0.0;   }
   void moveForward();
   // bullet mechanics
   void shootBullets() { bullets.push_back(Bullet(*this)); }
   void moveBullets(double time);
   void drawBullets(ogstream& gout);

private:
   double thrust;
   vector<Bullet> bullets;
};
