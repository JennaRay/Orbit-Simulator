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
#include <functional>

using namespace std;

class Satellite : public Orbiter
{
public:
   //Constructors
   Satellite() : Orbiter() {}
   Satellite(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided) : Orbiter(position, velocity, angle, acceleration, radius, isCollided) {}

   void collide() override {
      setCollide(true);
      breakApart();
   }
   void draw(ostream& gout) {}
   virtual void breakApart() {}
   virtual void moveParts(double time) {};

private:
   Orbiter* parts[5]; // holds all pieces, parts, fragments when satellite breaks apart
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

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
private:
   Orbiter* parts[4]; // holds all pieces, parts, fragments when sputnik breaks apart
   int arraySize = 4;
};

class GPS : public Satellite
{
public:
   GPS() : Satellite() { setRadius(12); }
   GPS(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided) : Satellite(position, velocity, angle, acceleration, radius, isCollided) {}

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
private:
   Orbiter* parts[3]; // holds all pieces, parts, fragments when GPS breaks apart
   int arraySize = 3;
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

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
private:
   Orbiter* parts[4]; // breaks into 4 pieces
   int arraySize = 4;
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

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
private:
   Orbiter* parts[5]; // breaks into 3 pieces and 2 fragments
   int arraySize = 5;
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

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
private:
   Orbiter* parts[4]; // breaks into 2 pieces and 2 fragments
   int arraySize = 4;
};

class Piece : public Satellite
{
public:
   Piece(Orbiter& parent, double radius) : Satellite(parent.getPosition(), parent.getVelocity(), parent.getAngle(), parent.getAcceleration(), radius, false) { kick(); };

   virtual void draw(ogstream& gout) {}; // to be overidden
   virtual void breakApart() {}; // to be overidden
   void kick();
private:
};
//GiantPiece breaks into 4 parts
class GiantPiece : public Piece
{
public:
   GiantPiece(Orbiter& parent, double radius) : Piece(parent, radius) {};
   virtual void draw(ogstream& gout) {};
   void breakApart() override;
private:
   Orbiter* parts[4]; //  fragments when GPS center breaks apart
   int arraySize = 4;
};
//BigPiece breaks into 3 parts
class BigPiece : public Piece
{
public:
   BigPiece(Orbiter& parent, double radius) : Piece(parent, radius) {};

   void draw(ogstream& gout) {};
   void breakApart() override;
private:
   Orbiter* parts[3]; //  fragments when GPS center breaks apart
   int arraySize = 3;
};

//SmallPiece breaks into 2 parts
class SmallPiece : public Satellite
{
public:
   SmallPiece(Orbiter& parent, double radius) : Satellite(parent.getPosition(), parent.getVelocity(), parent.getAngle(), parent.getAcceleration(), radius, false) {};

   void draw(ogstream& gout) {};
   void breakApart() override;
private:
   Orbiter* parts[2]; //  fragments when GPS center breaks apart
   int arraySize = 2;
};
/*ALL the individual piece classes just need draw functions*/
//GPS pieces
class GPSCenter : public BigPiece
{
public:
   GPSCenter(Orbiter& parent) : BigPiece(parent, 7) {};

   void draw(ogstream& gout) override { gout.drawGPSCenter(getPosition(), getSpin()); }
};

class GPSLeft : public BigPiece
{
public:
   GPSLeft(Orbiter& parent) : BigPiece(parent, 8) {};

   void draw(ogstream& gout) override { gout.drawGPSLeft(getPosition(), getSpin()); }
};

class GPSRight : public BigPiece
{
public:
   GPSRight(Orbiter& parent) : BigPiece(parent, 8) {};

   void draw(ogstream& gout) override { gout.drawGPSRight(getPosition(), getSpin()); }
};

//HUBBLE PIECES
class HubbleTelescope : public BigPiece
{
public:
   HubbleTelescope(Orbiter& parent) : BigPiece(parent, 10) {};

   void draw(ogstream& gout) override { gout.drawHubbleTelescope(getPosition(), getSpin()); }
};

class HubbleComputer : public SmallPiece
{
public:
   HubbleComputer(Orbiter& parent) : SmallPiece(parent, 7) {};

   void draw(ogstream& gout) override { gout.drawHubbleComputer(getPosition(), getSpin()); }
};

class HubbleLeft : public SmallPiece
{
public:
   HubbleLeft(Orbiter& parent) : SmallPiece(parent, 8) {};

   void draw(ogstream& gout) override { gout.drawHubbleLeft(getPosition(), getSpin()); }
};

class HubbleRight : public SmallPiece
{
public:
   HubbleRight(Orbiter& parent) : SmallPiece(parent, 8) {};

   void draw(ogstream& gout) override { gout.drawHubbleRight(getPosition(), getSpin()); }
};

//DRAGON PIECES
class DragonCenter : public GiantPiece
{
public:
   DragonCenter(Orbiter& parent) : GiantPiece(parent, 6) {};

   void draw(ogstream& gout) override { gout.drawCrewDragonCenter(getPosition(), getSpin()); }
};

class DragonLeft : public SmallPiece
{
public:
   DragonLeft(Orbiter& parent) : SmallPiece(parent, 6) {};

   void draw(ogstream& gout) override { gout.drawCrewDragonLeft(getPosition(), getSpin()); }
};

class DragonRight : public SmallPiece
{
public:
   DragonRight(Orbiter& parent) : SmallPiece(parent, 6) {};

   void draw(ogstream& gout) override { gout.drawCrewDragonRight(getPosition(), getSpin()); }
};

//STARLINK PIECES
class StarlinkBody : public BigPiece
{
public:
   StarlinkBody(Orbiter& parent) : BigPiece(parent, 2) {};

   void draw(ogstream& gout) override { gout.drawStarlinkBody(getPosition(), getSpin()); }
};

class StarlinkArray : public BigPiece
{
public:
   StarlinkArray(Orbiter& parent) : BigPiece(parent, 4) {};

   void draw(ogstream& gout) override { gout.drawStarlinkArray(getPosition(), getSpin()); }
};