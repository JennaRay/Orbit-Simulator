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
      construct_default();
      testRotate_left();
      testRotate_right();
      testRotate_nothing();
      test_applyThrust();
      test_stopThrust();
      testMoveForward_noThrust();
      //testMoveForward_withThrust(); idk how to do the math for this one :(

      report("SpacePlane");
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
      SpacePlane s = SpacePlane();

      // verify
      assertEquals(s.position.x, position.x);
      assertEquals(s.position.y, position.y);
      assertEquals(s.velocity.dx, velocity.dx);
      assertEquals(s.velocity.dy, velocity.dy);
      assertEquals(s.angle.radians, angle.radians);
      assertEquals(s.acceleration.ddx, acceleration.ddx);
      assertEquals(s.acceleration.ddy, acceleration.ddy);
      assertEquals(s.isCollided, isCollided);
      assertEquals(s.radius, radius);
   }
   void testRotate_left()
   {
      //setup
      SpacePlane sp;
      double initialSpin = sp.getSpin();

      // exercise
      sp.rotate(-1);

      // verify
      assertEquals(sp.getSpin(), initialSpin - 1);
   }
   void testRotate_right()
   {
      //setup
      SpacePlane sp;
      double initialSpin = sp.getSpin();

      // exercise
      sp.rotate(1);

      // verify
      assertEquals(sp.getSpin(), initialSpin + 1);
   }
   void testRotate_nothing()
   {
      //setup
      SpacePlane sp;
      double initialSpin = sp.getSpin();

      // exercise
      sp.rotate(0);

      // verify
      assertEquals(sp.getSpin(), initialSpin);
   }
   void test_applyThrust()
   {
      // setup
      SpacePlane sp;
      double initialThrust = sp.thrust;

      // exercise
      sp.applyThrust();

      //// verify
      assertEquals(sp.thrust, 200000.0);
   }

   void test_stopThrust()
   {
      // setup
      SpacePlane sp;
      sp.thrust = 200000.0; // set thrust to a non-zero value

      // exercise
      sp.stopThrust();

      // verify
      assertEquals(sp.thrust, 0.0);
   }

   void testMoveForward_noThrust()
   {
      // setup
      SpacePlane sp;
      sp.thrust = 0.0;
      sp.velocity = Velocity(0, 0);
      sp.acceleration = Acceleration(0, 0);
      Position initialPosition = sp.getPosition();

      // exercise
      sp.moveForward();

      // verify
      assertEquals(sp.getPosition().getMetersX(), initialPosition.getMetersX());
      assertEquals(sp.getPosition().getMetersY(), initialPosition.getMetersY());
   }

   void testMoveForward_withThrust() //idk how to do the math for this one without just copying the code in move forward
   {
      // setup
      SpacePlane sp;
      sp.thrust = 200000.0; // set thrust to a non-zero value
      sp.velocity = Velocity(0, 0);
      sp.acceleration = Acceleration(0, 0);


      // exercise
      sp.moveForward();

      // verify

   }
   // Add more test cases for other methods and functionalities as needed
};