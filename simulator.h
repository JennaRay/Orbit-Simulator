/***********************************************************************
 * Header File:
 *    Point : To run a simulation of the orbit programm
 * Author:
 *    Jenna Ray
 * Summary:
 *    Instance of the orbiter simulator
 ************************************************************************/
#pragma once

#include <iostream>
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include "orbiter.h"
#include "satellite.h"

using namespace std;

class Simulator
{
public:
   //Constructors
   Simulator(Position UpperRight) : upperRight(UpperRight), angleEarth(Angle(0.0)), earthPos(Position()), time(24) {}

   void display(ogstream& gout);
   void checkCollisions() {}
   void handleCollisions(Orbiter delta) {}
   void moveOrbiters();
   void movePlane() {}
   void rotateEarth() {}

private:
   Angle angleEarth;
   Position earthPos;
   Position upperRight;
   double time;
   //Spaceplane dreamChaser
   //satellites
   //Orbiter orbiters[]; //maybe we do individual things for now of every satellite
   Sputnik sputnik;
   
};