#pragma once
#include "unitTest.h"
#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "acceleration.h"
#include "orbiter.h"
#include "satellite.h"
#include "spaceplane.h"
#include "simulator.h"

class TestSimulator : public UnitTest
{
public:
   void run()
   {
      //call all test cases here 
      testCheckCollisions_planeAndSatteliteSamePosition();
      testCheckCollisions_sattelitesSamePosition();
      testCheckCollisions_planeAndSatteliteNotColliding();
      testCheckCollisions_sattelitesNotColliding();
      testCheckCollisions_planeAndSatteliteDifferentPositions();
      testCheckCollisions_sattelitesDifferentPositions();
     

      report("Simulator");
   }
private:
   void testCheckCollisions_planeAndSatteliteSamePosition()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setMeters(0.0, 0.0); // GPS1
      sim.dreamChaser.position.setMeters(0.0, 0.0); // plane

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, true);
      assertEquals(sim.dreamChaser.isCollided, true);
   }

   void testCheckCollisions_sattelitesSamePosition()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setMeters(0.0, 0.0); // GPS1
      sim.orbiters[2]->position.setMeters(0.0, 0.0); // GPS2

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, true);
      assertEquals(sim.orbiters[2]->isCollided, true);

   }
   void testCheckCollisions_planeAndSatteliteNotColliding()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setPixelsX(0.0); // GPS1
      sim.orbiters[1]->position.setPixelsY(0.0); // GPS1
      sim.dreamChaser.position.setPixelsX(100.0); // plane
      sim.dreamChaser.position.setPixelsY(100.0); // plane

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, false);
      assertEquals(sim.dreamChaser.isCollided, false);

   }
   void testCheckCollisions_sattelitesNotColliding()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setPixelsX(0.0); // GPS1
      sim.orbiters[1]->position.setPixelsY(0.0); // GPS1
      sim.orbiters[2]->position.setPixelsX(100.0); // GPS2
      sim.orbiters[2]->position.setPixelsY(100.0); // GPS2

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, false);
      assertEquals(sim.orbiters[2]->isCollided, false);

   }

   void testCheckCollisions_planeAndSatteliteDifferentPositions()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setMeters(0.0, 0.0); // GPS1
      sim.dreamChaser.position.setMeters(100.0, 100.0); // plane

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, true);
      assertEquals(sim.dreamChaser.isCollided, true);

   }

   void testCheckCollisions_sattelitesDifferentPositions()
   {
      //setup
      Position ptUpperRight;
      ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
      ptUpperRight.setPixelsX(1000.0);
      ptUpperRight.setPixelsY(1000.0);
      Simulator sim(ptUpperRight);
      sim.orbiters[1]->position.setMeters(0.0, 0.0); // GPS1
      sim.orbiters[2]->position.setMeters(0.0, 0.0); // GPS2

      // exercise
      sim.checkCollisions();

      // verify
      assertEquals(sim.orbiters[1]->isCollided, true);
      assertEquals(sim.orbiters[2]->isCollided, true);
   }

};
