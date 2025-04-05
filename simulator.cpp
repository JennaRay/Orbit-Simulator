#include <iostream>
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include "orbiter.h"
#include "satellite.h"
#include "simulator.h"
#include "uiInteract.h"


/****************************************
* DISPLAY
* display all of the sattelites, and the earth, and the plane
*****************************************/
void Simulator::display(ogstream& gout)
{
   //display earth
   gout.drawEarth(earthPos, angleEarth.getRadians());

   //display satellites
   for (int i = 0; i < 10; i++)
   {
      orbiters[i]->draw(gout);
   }

   //display plane
   dreamChaser.draw(gout);
   // draw bullets
   dreamChaser.drawBullet(gout);
}

/****************************************************************
* CHECK COLLISIONS
* Check if any of the orbiters have collided with the plane or each other
*************************************************************/
void Simulator::checkCollisions()
{
   //check if the plane has collided with any of the orbiters
   for (int i = 0; i < 10; i++)
   {
      if (orbiters[i]->checkIsCollided())
      {
         orbiters[i]->checkPartsCollisions(dreamChaser); // check if the plane has collided with the parts of the orbiter
         vector<Bullet> bullets = dreamChaser.getBullets();
         for (auto& bullet : bullets)
         {
            orbiters[i]->checkPartsCollisions(bullet); // check if any bullets have collided with the parts of the orbiter
         }
      }
      else
      {
         if (dreamChaser.hasBullets())
         {
            //check if bullets have collided with orbiter
            vector<Bullet> bullets = dreamChaser.getBullets();
            for (auto& bullet : bullets)
            {
               if (computeDistance(bullet.getPosition(), orbiters[i]->getPosition()) < (bullet.getRadiusMeters() + orbiters[i]->getRadiusMeters()))
               {
                  orbiters[i]->collide(); // call collide on the orbiter
                  bullet.collide(); // mark the bullet as collided
                  break; // exit the loop since the bullet has collided
               }
            }
         }
         if (computeDistance(dreamChaser.getPosition(), orbiters[i]->getPosition()) < (dreamChaser.getRadiusMeters() + orbiters[i]->getRadiusMeters()))
         {
            orbiters[i]->collide();
            dreamChaser.collide();
         }
         for (int j = i + 1; j < 10; j++)
         {
            if (i != j) // avoid self-collision check
            {
               // check if j is split into parts
               if (orbiters[j]->checkIsCollided())
                  continue; // skip if the orbiter is already collided
               //will change to individual parts later   
               else
               {
                  //check if the two orbiters have collided
                  if (computeDistance(orbiters[i]->getPosition(), orbiters[j]->getPosition()) < (orbiters[i]->getRadiusMeters() + orbiters[j]->getRadiusMeters()))
                  {
                     orbiters[i]->collide();
                     orbiters[j]->collide();
                  }
               }
            }
         }
      }
   }
  
}


/*********************************************
*MOVE ORBITERS
* Move all of the things orbiting the earth (satellites, pieces, plane)
**********************************************/
void Simulator::moveOrbiters()
{
   //move orbiters
   for (int i = 0; i < 10; i++)
   {
      //check if the orbiter is collided (whole or split into parts)
      if (orbiters[i]->checkIsCollided())
      {
         orbiters[i]->moveParts(time);
      }
      else
         orbiters[i]->move(time);
   }
   //move dreamChaser
   dreamChaser.move(time);
   // move bullets
   dreamChaser.moveBullet(time);
}

/***********************************************
*HANDLE INPUT
* Take input from the interface and move the plane based on it
************************************************/
void Simulator::handleInput(const Interface* pUI)
{
    // Movement
   if (pUI->isLeft())
      dreamChaser.rotate(-0.1);
   if (pUI->isRight())
      dreamChaser.rotate(0.1);
   if (pUI->isDown())
      dreamChaser.applyThrust();
   else
      dreamChaser.stopThrust();

   // Fire bullets
   if (pUI->isSpace())
       dreamChaser.shootBullet();
}