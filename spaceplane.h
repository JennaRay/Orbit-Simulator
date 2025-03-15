#pragma once

#include "orbiter.h"
#include "velocity.h"
#include "position.h"
#include "angle.h"
#include "uiDraw.h"

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

private:
   double thrust;
};
