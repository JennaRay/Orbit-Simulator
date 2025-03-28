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
}

/****************************************************************
* CHECK COLLISIONS
* Check if any of the orbiters have collided with the plane or each other
*************************************************************/
void Simulator::checkCollisions()
{
   //check if the plane has collided with any of the orbiters

}


/**8****************************************
*MOVE ORBITERS
* Move all of the things orbiting the earth (satellites, pieces, plane)
**********************************************/
void Simulator::moveOrbiters()
{
   //move orbiters
   for (int i = 0; i < 10; i++)
   {
         orbiters[i]->move(time);
   }
   //move dreamChaser
   dreamChaser.move(time);
}

/***********************************************
*HANDLE INPUT
* Take input from the interface and move the plane based on it
************************************************/
void Simulator::handleInput(const Interface* pUI)
{
   if (pUI->isLeft())
      dreamChaser.rotate(-0.1);
   if (pUI->isRight())
      dreamChaser.rotate(0.1);
   if (pUI->isDown())
      dreamChaser.applyThrust();
   else
      dreamChaser.stopThrust();
}