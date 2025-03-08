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