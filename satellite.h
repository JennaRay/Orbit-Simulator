/***********************************************************************
 * Header File:
 *    Point : The representation of an satellite orbiter
 * Author:
 *    Jenna Ray
 * Summary:
 *    Satellite orbiter subclass object.
 ************************************************************************/

#pragma once

#include <iostream>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "orbiter.h"

using namespace std;

class Satellite : public Orbiter
{
public:
   //Constructors
   Satellite() : Orbiter() {}
   Satellite(Position position, Velocity velocity, Angle angle, Acceleration acceleration, bool isCollided) : Orbiter(position, velocity, angle, acceleration, isCollided) {}

   void collide() override {}
   void draw(ostream& gout) {}
   void breakApart() {}

private:

   //Piece pieces[];
   //Fragment fragments[]; //this doesn't work with the sub classes hmmm
};

//specific satellite subclasses

class Sputnik : public Satellite
{
public:
   //Constructors
   Sputnik() : Satellite() 
   {
      Position pos(-36515095.13, 21082000.0);
      Velocity v(2050, 2684.68);

      setPosition(pos);
      setVelocity(v);
   }

   void draw(ogstream& gout) { gout.drawSputnik(getPosition(), getAngle().getRadians()); }
private:
   // add fragments
};

class GPS : public Satellite
{
public:
   GPS() : Satellite() {}
   GPS(Position position, Velocity velocity, Angle angle, Acceleration acceleration, bool isCollided) : Satellite(position, velocity, angle, acceleration, isCollided) {}

   void draw(ogstream& gout) { gout.drawGPS(getPosition(), getAngle().getRadians()); }
private:
   // breaks into 3 pieces and 2 fragments
};