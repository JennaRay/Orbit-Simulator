/***********************************************************************
 * Header File:
 *    Point : The representation of an orbiter
 * Author:
 *    Jenna Ray
 * Summary:
 *    Baseclass for the orbiter object.
 ************************************************************************/

#pragma once

#include <iostream>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "uiDraw.h"

using namespace std;

class TestOrbiter;

class Orbiter
{
public:
   friend TestOrbiter;

   //Constructors
   Orbiter() : position(Position()), velocity(Velocity()), angle(Angle()), acceleration(Acceleration()), isCollided(false), spin(0.0), orbitCenter(Position(0, 0)) { orbitCenter.setMeters(0, 0); }
   Orbiter(Position position, Velocity velocity, Angle angle, Acceleration acceleration, bool isCollided) : position(position), velocity(velocity), angle(angle), acceleration(acceleration), isCollided(isCollided), spin(0.0), orbitCenter(Position(0,0)) {}
   Orbiter(const Orbiter& orbiter) : position(orbiter.position), velocity(orbiter.velocity), angle(orbiter.angle), acceleration(orbiter.acceleration), isCollided(orbiter.isCollided), spin(orbiter.spin), orbitCenter(orbiter.orbitCenter) {}
   Orbiter& operator=(const Orbiter& orbiter)
   {
      if (this != &orbiter)
      {
         position = orbiter.position;
         velocity = orbiter.velocity;
         angle = orbiter.angle;
         acceleration = orbiter.acceleration;
         isCollided = orbiter.isCollided;
         spin = orbiter.spin;
         orbitCenter = orbiter.orbitCenter;
      }
      return *this;
   }
   //Getters
   virtual Position getPosition() const { return position; }
   virtual Velocity getVelocity() const { return velocity; }
   virtual Angle getAngle() const { return angle; }
   virtual Acceleration getAcceleration() const { return acceleration; }
   virtual bool checkIsCollided() const { return isCollided; }
   virtual double getSpin() { return spin; }

   //Setters
   virtual void setPosition(Position position) { this->position = position; }
   virtual void setVelocity(Velocity velocity) { this->velocity = velocity; }
   virtual void setAngle(Angle angle) { this->angle = angle; }
   virtual void setAcceleration(Acceleration acceleration) { this->acceleration = acceleration; }
   virtual void setSpin(double delta) { spin = delta; }

   virtual void move(double time);
   virtual void collide() {};
   virtual void draw(ogstream& gout) {};

private:
   Position position;
   Position orbitCenter;
   Velocity velocity;
   Angle angle;
   Acceleration acceleration;
   double spin;
   bool isCollided;
};


//Part subclass

class Part : public Orbiter
{
public:
   //Constructors
   Part() : Orbiter() {}

   void collide() override {}
   void draw(ogstream& gout) {}
};

//Piece subclass

class Piece : public Orbiter
{
public:
   //Constructors
   Piece() : Orbiter() {}

   void collide() override {}
   void draw(ogstream& gout) {}
   void breakApart() {}

private:

   //Part parts[];
};

//Fragment subclass

class Fragment : public Orbiter
{
public:
   //Constructors
   Fragment() : Orbiter() {}

   void collide()  {}
   void draw(ogstream& gout) {}
   double kick(Velocity c) {}
   void retire() {}
private:
   int retireTime;
};