#pragma once

#include "unitTest.h"
#include "spaceplane.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "acceleration.h"
#include "orbiter.h"
#include <math.h>   // for M_PI which is 3.14159
#include <iostream>
using namespace std;

class TestSpacePlane : public UnitTest
{
public:
   void run()
   {
      //call all test cases here   Everything is saying undeclaired identifier even though I'm declaring it
      //construct_default();
      //testRotate_left();
      //testRotate_right();
      //testRotate_nothing();
      //test_applyThrust();
   }
private:
   //test cases
   void construct_default()
   {
      // setup
      Position position;
      position.setPixelsX(-450);
      position.setPixelsY(450);
      Velocity velocity(0.0, -2000);
      Angle angle;
      Acceleration acceleration;
      double radius = 10.0;
      bool isCollided = false;

      // exercise
      //SpacePlane s = SpacePlane();

      //// verify
      //assertEquals(s.position.x, position.x);
      //assertEquals(s.position.y, position.y);
      //assertEquals(s.velocity.dx, velocity.dx);
      //assertEquals(s.velocity.dy, velocity.dy);
      //assertEquals(s.angle.radians, angle.radians);
      //assertEquals(s.acceleration.ddx, acceleration.ddx);
      //assertEquals(s.acceleration.ddy, acceleration.ddy);
      //assertEquals(s.isCollided, isCollided);
      //assertEquals(s.radius, radius);
   }
   void testRotate_left()
   {

   }
   void testRotate_right()
   {

   }
   void testRotate_nothing()
   {

   }
   void test_applyThrust()
   {
      // setup
      //SpacePlane sp;
      //double initialThrust = sp.thrust;

      // exercise
      //sp.applyThrust();

      //// verify
      //assertEquals(sp.thrust, 200000.0);
   }

   // Add more test cases for other methods and functionalities as needed
};