/***********************************************************************
 * Header File:
 *    Test Orbiter : Test the Orbiter class
 * Author:
 *    Jenna Ray
 * Summary:
 *    All the unit tests for Orbiter
 ************************************************************************/

#pragma once

#include "orbiter.h"
#include "unitTest.h"
#include "position.h"
#include "angle.h"
#include "velocity.h"
#include "acceleration.h"

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestOrbiter : public UnitTest
{
public:
   void run()
   {
      //call all test cases here
      construct_default();
      construct_nonDefault();
      construct_copy();
      operator_equels();

      testGetters_getPosition();
      testGetters_getVelocity();
      testGetters_getAngle();
      testGetters_getAcceleration();
      testGetters_checkIsCollided();

      testSetters_setAcceleration();
      testSetters_setAngle();
      testSetters_setPosition();
      testSetters_setVelocity();

      // need tests for move and collide

      report("Orbiter");
   }
private:
   //test cases
   void construct_default()
   {
      // setup
      Position position;
      Velocity velocity;
      Angle angle;
      Acceleration acceleration;
      bool isCollided = false;

      // exercise
      Orbiter orbiter;

      // verify
      assertEquals(orbiter.position.x, position.x);
      assertEquals(orbiter.position.y, position.y);
      assertEquals(orbiter.velocity.dx, velocity.dx);
      assertEquals(orbiter.velocity.dy, velocity.dy);
      assertEquals(orbiter.angle.radians, angle.radians);
      assertEquals(orbiter.acceleration.ddx, acceleration.ddx);
      assertEquals(orbiter.acceleration.ddy, acceleration.ddy);
      assertEquals(orbiter.isCollided, isCollided);
   }

   void construct_nonDefault()
   {
      // setup
      Position position(1.0, 2.0);
      Velocity velocity(3.0, 4.0);
      Angle angle(5.0);
      Acceleration acceleration(6.0, 7.0);
      bool isCollided = true;
      double radius = 10.0;

      // exercise
      Orbiter orbiter(position, velocity, angle, acceleration, radius, isCollided);

      // verify
      assertEquals(orbiter.position.x, position.x);
      assertEquals(orbiter.position.y, position.y);
      assertEquals(orbiter.velocity.dx, velocity.dx);
      assertEquals(orbiter.velocity.dy, velocity.dy);
      assertEquals(orbiter.angle.radians, angle.radians);
      assertEquals(orbiter.acceleration.ddx, acceleration.ddx);
      assertEquals(orbiter.acceleration.ddy, acceleration.ddy);
      assertEquals(orbiter.isCollided, isCollided);
      assertEquals(orbiter.radius, radius);
   }

   void construct_copy()
   {
      //setup
      Position position(1.0, 2.0);
      Velocity velocity(3.0, 4.0);
      Angle angle(5.0);
      Acceleration acceleration(6.0, 7.0);
      bool isCollided = true;
      double radius = 10.0;

      Orbiter orbiter(position, velocity, angle, acceleration, radius, isCollided);

      // exercise
      Orbiter copyOrbiter(orbiter);

      // verify
      assertEquals(copyOrbiter.position.x, position.x);
      assertEquals(copyOrbiter.position.y, position.y);
      assertEquals(copyOrbiter.velocity.dx, velocity.dx);
      assertEquals(copyOrbiter.velocity.dy, velocity.dy);
      assertEquals(copyOrbiter.angle.radians, angle.radians);
      assertEquals(copyOrbiter.acceleration.ddx, acceleration.ddx);
      assertEquals(copyOrbiter.acceleration.ddy, acceleration.ddy);
      assertEquals(copyOrbiter.isCollided, isCollided);
      assertEquals(copyOrbiter.radius, radius);
   }

   void operator_equels()
   {
      //setup
      Position pos(4.0, 4.0);
      Velocity v(1.0, 2.0);
      Angle angle(5.0);
      Acceleration a(6.0, 7.0);
      bool isCollided = false;
      double radius = 10.0;
      Orbiter orbiter(pos, v, angle, a, radius, isCollided);

      //exercise
      Orbiter newOrbiter;
      newOrbiter = orbiter;

      //verify
      assertEquals(newOrbiter.position.x, pos.x);
      assertEquals(newOrbiter.position.y, pos.y);
      assertEquals(newOrbiter.velocity.dx, v.dx);
      assertEquals(newOrbiter.velocity.dy, v.dy);
      assertEquals(newOrbiter.angle.radians, angle.radians);
      assertEquals(newOrbiter.acceleration.ddx, a.ddx);
      assertEquals(newOrbiter.acceleration.ddy, a.ddy);
      assertEquals(newOrbiter.isCollided, isCollided);
      assertEquals(newOrbiter.radius, radius);
   }
   //getters
   void testGetters_getPosition()
   {
      //setup
      Orbiter orbiter;
      Position position(8.0, 9.0);
      orbiter.position = position;

      //exercise
      Position result = orbiter.getPosition();
      //verify
      assertEquals(result.x, 8.0);
      assertEquals(result.y, 9.0);
   }

   void testGetters_getVelocity()
   {
      //setup
      Orbiter orbiter;
      Velocity velocity(8.0, 9.0);
      orbiter.velocity = velocity;

      //exercise
      Velocity result = orbiter.getVelocity();

      //verify
      assertEquals(result.dx, 8.0);
      assertEquals(result.dy, 9.0);
   }

   void testGetters_getAngle()
   {
      //setup
      Orbiter orbiter;
      Angle angle;
      angle.radians = 8.0;
      orbiter.angle = angle;

      //exercise
      Angle result = orbiter.getAngle();

      //verify
      assertEquals(result.radians, 8.0);
   }

   void testGetters_getAcceleration()
   {
      //setup
      Orbiter orbiter;
      Acceleration acceleration(8.0, 9.0);
      orbiter.acceleration = acceleration;

      //exercise
      Acceleration result = orbiter.getAcceleration();

      //verify
      assertEquals(result.ddx, 8.0);
      assertEquals(result.ddy, 9.0);
   }

   void testGetters_checkIsCollided()
   {
      //setup
      Orbiter orbiter;
      bool isCollided = true;
      orbiter.isCollided = isCollided;

      //exercise
      bool result = orbiter.checkIsCollided();

      //verify
      assertEquals(result, true);
   }

   //setters
   void testSetters_setPosition()
   {
       //setup
       Orbiter orbiter;
       Position position(8.0, 9.0);

       //exercise
       orbiter.setPosition(position);

       //verify
       assertEquals(orbiter.position.x, 8.0);
       assertEquals(orbiter.position.y, 9.0);
   }

   void testSetters_setVelocity()
   {
       //setup
       Orbiter orbiter;
       Velocity velocity(8.0, 9.0);

       //exercise
       orbiter.setVelocity(velocity);

       //verify
       assertEquals(orbiter.velocity.dx, 8.0);
       assertEquals(orbiter.velocity.dy, 9.0);
   }

   void testSetters_setAngle()
   {
       //setup
       Orbiter orbiter;
       Angle angle(8.0);

       //exercise
       orbiter.setAngle(angle);

       //verify
       assertEquals(orbiter.angle.radians, 8.0 * M_PI / 180.0);
   }

   void testSetters_setAcceleration()
   {
       //setup
       Orbiter orbiter;
       Acceleration acceleration(8.0, 9.0);

       //exercise
       orbiter.setAcceleration(acceleration);

       //verify
       assertEquals(orbiter.acceleration.ddx, 8.0);
       assertEquals(orbiter.acceleration.ddy, 9.0);
   }

   void testMove()
   {
       //setup
       Orbiter orbiter;
       orbiter.setPosition(Position(5.0, 5.0));
       orbiter.setVelocity(Velocity(2.0, 3.0));

       //exercise
       orbiter.move(24);

       //verify
       assertEquals(orbiter.position.x, 7.0);
       assertEquals(orbiter.position.y, 8.0);
   }

   // add collision when collision is required.

};