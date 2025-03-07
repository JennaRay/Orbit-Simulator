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

using namespace std;

class Orbiter
{
public:
   //Constructors
   Orbiter() : position(Position()), velocity(Velocity()), angle(Angle()), acceleration(Acceleration()), isCollided(false) {}
   Orbiter(Position position, Velocity velocity, Angle angle, double acceleration, bool isCollided) : position(position), velocity(velocity), angle(angle), acceleration(acceleration), isCollided(isCollided) {}
   Orbiter(const Orbiter& orbiter) : position(orbiter.position), velocity(orbiter.velocity), angle(orbiter.angle), acceleration(orbiter.acceleration), isCollided(orbiter.isCollided) {}

   //Getters
   Position getPosition() const { return position; }
   Velocity getVelocity() const { return velocity; }
   Angle getAngle() const { return angle; }
   Acceleration getAcceleration() const { return acceleration; }
   bool checkIsCollided() const { return isCollided; }

   //Setters
   void setPosition(Position position) { this->position = position; }
   void setVelocity(Velocity velocity) { this->velocity = velocity; }
   void setAngle(Angle angle) { this->angle = angle; }
   void setAcceleration(Acceleration acceleration) { this->acceleration = acceleration; }

   void move() {}
   virtual void collide() {}
   virtual void draw() {}

private:
   Position position;
   Velocity velocity;
   Angle angle;
   Acceleration acceleration;
   bool isCollided;
};


//Part subclass

class Part : public Orbiter
{
public:
   //Constructors
   Part() : Orbiter() {}

   void collide() override {}
   void draw() override {}
};

//Piece subclass

class Piece : public Orbiter
{
public:
   //Constructors
   Piece() : Orbiter() {}

   void collide() override {}
   void draw() override {}
   void breakApart() {}

private:

   Part parts[];
};

//Fragment subclass

class Fragment : public Orbiter
{
public:
   //Constructors
   Fragment() : Orbiter() {}

   void collide() override {}
   void draw() override {}
   double kick(Velocity c) {}
   void retire() {}
private:
   int retireTime;
};