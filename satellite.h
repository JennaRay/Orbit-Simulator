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
   Satellite(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided) : Orbiter(position, velocity, angle, acceleration, radius, isCollided) {}

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
      setSpin(atan2(0 - getVelocity().getDX(), 0 - getVelocity().getDY()));
      setRadius(4); // radius in pixels
   }

   void draw(ogstream& gout) { gout.drawSputnik(getPosition(), getSpin()); }
private:
   // add fragments
};

class GPS : public Satellite
{
public:
   GPS() : Satellite() { setRadius(12); }
   GPS(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided) : Satellite(position, velocity, angle, acceleration, radius, isCollided) {}

   void draw(ogstream& gout) { gout.drawGPS(getPosition(), getSpin()); }
private:
   // breaks into 3 pieces and 2 fragments
};

class Hubble : public Satellite
{
public:
   Hubble() : Satellite()
   {
      Position pos(0.0, -42164000.0);
      Velocity v(3100.0, 0.0);

      setPosition(pos);
      setVelocity(v);
      setRadius(10); // radius in pixels
   }

   void draw(ogstream& gout) { gout.drawHubble(getPosition(), getSpin()); }
};

class Dragon : public Satellite
{
public:
   Dragon() : Satellite()
   {
      Position pos(0.0, 8000000.0);
      Velocity v(-7900.0, 0.0);

      setPosition(pos);
      setVelocity(v);
      setRadius(7); // radius in pixels
   }

   void draw(ogstream& gout) { gout.drawCrewDragon(getPosition(), getSpin()); }
private:
   // breaks into 3 pieces and 2 fragments
};

class Starlink : public Satellite
{
public:
   Starlink() : Satellite() 
   {
      Position pos(0.0, -13020000.0);
      Velocity v(5800.0, 0.0);

      setPosition(pos);
      setVelocity(v);
      setRadius(6); // radius in pixels
   }

   void draw(ogstream& gout) { gout.drawStarlink(getPosition(), getSpin()); }
};