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
#include "spaceplane.h"
#include "uiInteract.h"
#include <vector>

using namespace std;

class TestSimulator;

class Simulator
{
public:
   friend TestSimulator;
   //Constructors
   Simulator(Position UpperRight) : upperRight(UpperRight), angleEarth(Angle(0.0)), earthPos(Position()), time(24) 
   {

      //set up the GPSs
      Position gps1Pos(0,0);
      gps1Pos.setZoom(UpperRight.getZoom());
      gps1Pos.setMeters(0.0, 26560000.0);
      Velocity gps1Vol(-3880.0, 0.0);
      //gps1 = GPS(gps1Pos, gps1Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps1.setSpin(atan2(0 - gps1.getVelocity().getDX(), 0 - gps1.getVelocity().getDY()));

      Position gps2Pos(0,0);
      gps2Pos.setZoom(UpperRight.getZoom());
      gps2Pos.setMeters(23001634.72, 13280000.0);
      Velocity gps2Vol(-1940.0, 3360.18);
      //gps2 = GPS(gps2Pos, gps2Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps2.setSpin(atan2(0 - gps2.getVelocity().getDX(), 0 - gps2.getVelocity().getDY()));

      Position gps3Pos(0,0);
      gps3Pos.setZoom(UpperRight.getZoom());
      gps3Pos.setMeters(23001634.72, -13280000.0);
      Velocity gps3Vol(1940.0, 3360.18);
      //gps3 = GPS(gps3Pos, gps3Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps3.setSpin(atan2(0 - gps3.getVelocity().getDX(), 0 - gps3.getVelocity().getDY()));

      Position gps4Pos(0,0);
      gps4Pos.setZoom(UpperRight.getZoom());
      gps4Pos.setMeters(0.0, -26560000.0);
      Velocity gps4Vol(3880.0, 0.0);
      //gps4 = GPS(gps4Pos, gps4Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps4.setSpin(atan2(0 - gps4.getVelocity().getDX(), 0 - gps4.getVelocity().getDY()));

      Position gps5Pos(0,0);
      gps5Pos.setZoom(UpperRight.getZoom());
      gps5Pos.setMeters(-23001634.72, -13280000.0);
      Velocity gps5Vol(1940.0, -3360.18);
      //gps5 = GPS(gps5Pos, gps5Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps5.setSpin(atan2(0 - gps5.getVelocity().getDX(), 0 - gps5.getVelocity().getDY()));

      Position gps6Pos(0,0);
      gps6Pos.setZoom(UpperRight.getZoom());
      gps6Pos.setMeters(-23001634.72, 13280000.0);
      Velocity gps6Vol(-1940.0, -3360.18);
      //gps6 = GPS(gps6Pos, gps6Vol, Angle(0.0), Acceleration(), 12.0, false);
      //gps6.setSpin(atan2(0 - gps6.getVelocity().getDX(), 0 - gps6.getVelocity().getDY()));

      orbiters[0] = new Sputnik();
      orbiters[1] = new GPS(gps1Pos, gps1Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[2] = new GPS(gps2Pos, gps2Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[3] = new GPS(gps3Pos, gps3Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[4] = new GPS(gps4Pos, gps4Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[5] = new GPS(gps5Pos, gps5Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[6] = new GPS(gps6Pos, gps6Vol, Angle(0.0), Acceleration(), 12.0, false);
      orbiters[7] = new Hubble();
      orbiters[8] = new Dragon();
      orbiters[9] = new Starlink();

      for (int i = 1; i < 7; i++)
         orbiters[i]->setSpin(atan2(0 - orbiters[i]->getVelocity().getDX(), 0 - orbiters[i]->getVelocity().getDY()));

   }

   void display(ogstream& gout);
   void checkCollisions();
   void moveOrbiters();
   void movePlane() { dreamChaser.moveForward(); }
   void rotateEarth() { angleEarth.add(-0.02); }
   void handleInput(const Interface* pUI);

private:
   Orbiter* orbiters[10];
   Angle angleEarth;
   Position earthPos;
   Position upperRight;
   double time;
   SpacePlane dreamChaser;

};