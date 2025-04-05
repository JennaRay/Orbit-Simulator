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
   Satellite(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided = false) : Orbiter(position, velocity, angle, acceleration, radius, isCollided) {}

   void collide() override {
      setCollide(true);
      breakApart();
   }
   void updateSpin() override;
   void draw(ostream& gout) {}
   virtual void breakApart() {}
   virtual void moveParts(double time) {};
   virtual void checkPartsCollisions(Orbiter& orbiter) {}; // override in subclasses

private:
   Orbiter* parts[5]; // holds all pieces, parts, fragments when satellite breaks apart
   int arraySize = 5;
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
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[4]; // holds all pieces, parts, fragments when sputnik breaks apart
   int arraySize = 4;
};

class GPS : public Satellite
{
public:
   GPS() : Satellite() { setRadius(12); }
   GPS(Position position, Velocity velocity, Angle angle, Acceleration acceleration, double radius, bool isCollided = false) : Satellite(position, velocity, angle, acceleration, radius, isCollided) {}

   void draw(ogstream& gout);
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
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
   void checkPartsCollisions(Orbiter& orbiter) override;
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
   void checkPartsCollisions(Orbiter& orbiter) override;
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
   void checkPartsCollisions(Orbiter& orbiter) override;
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
   virtual void moveParts(double time) {};
   virtual void checkPartsCollisions(Orbiter& orbiter) {};
   void kick();
private:
};
/*ALL the individual piece classes just need draw functions*/
//GPS pieces
class GPSCenter : public Piece
{
public:
   GPSCenter(Orbiter& parent) : Piece(parent, 7) {};

   void draw(ogstream& gout) override 
   { 
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawGPSCenter(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};

class GPSLeft : public Piece
{
public:
   GPSLeft(Orbiter& parent) : Piece(parent, 8) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawGPSLeft(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};

class GPSRight : public Piece
{
public:
   GPSRight(Orbiter& parent) : Piece(parent, 8) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawGPSRight(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};

//HUBBLE PIECES
class HubbleTelescope : public Piece
{
public:
   HubbleTelescope(Orbiter& parent) : Piece(parent, 10) {};

   void draw(ogstream& gout) override 
   { 
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawHubbleTelescope(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};

class HubbleComputer : public Piece
{
public:
   HubbleComputer(Orbiter& parent) : Piece(parent, 7) {};

   void draw(ogstream& gout) override 
   { 
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawHubbleComputer(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[2];
   int arraySize = 2;
};

class HubbleLeft : public Piece
{
public:
   HubbleLeft(Orbiter& parent) : Piece(parent, 8) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawHubbleLeft(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[2];
   int arraySize = 2;
};

class HubbleRight : public Piece
{
public:
   HubbleRight(Orbiter& parent) : Piece(parent, 8) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawHubbleRight(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[2];
   int arraySize = 2;
};

//DRAGON PIECES
class DragonCenter : public Piece
{
public:
   DragonCenter(Orbiter& parent) : Piece(parent, 6) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawCrewDragonCenter(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[4];
   int arraySize = 4;
};

class DragonLeft : public Piece
{
public:
   DragonLeft(Orbiter& parent) : Piece(parent, 6) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawCrewDragonLeft(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[2];
   int arraySize = 2;
};

class DragonRight : public Piece
{
public:
   DragonRight(Orbiter& parent) : Piece(parent, 6) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawCrewDragonRight(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[2];
   int arraySize = 2;
};

//STARLINK PIECES
class StarlinkBody : public Piece
{
public:
   StarlinkBody(Orbiter& parent) : Piece(parent, 2) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawStarlinkBody(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};

class StarlinkArray : public Piece
{
public:
   StarlinkArray(Orbiter& parent) : Piece(parent, 4) {};

   void draw(ogstream& gout) override 
   {
      if (checkIsCollided())
      {
         for (int i = 0; i < arraySize; i++)
            parts[i]->draw(gout); // draw all parts (pieces) of the orbiter (satellite) that broke apart
      }
      else
         gout.drawStarlinkArray(getPosition(), getSpin()); 
   }
   void breakApart() override;
   void moveParts(double time) override;
   void checkPartsCollisions(Orbiter& orbiter) override;
private:
   Orbiter* parts[3];
   int arraySize = 3;
};