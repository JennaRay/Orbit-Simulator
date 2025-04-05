#pragma once
#include "satellite.h"
#include "position.h"

//Move parts could probably be inherited from satellite, but I'd have to figure out how to get the length of the array

void Satellite::updateSpin()
{
   double dx = getVelocity().getDX();
   double dy = getVelocity().getDY();

   double angularVelocity = (atan2(0 - dx, 0 - dy));
   addAngle(angularVelocity);
   if (angularVelocity > 0)
      addSpin(angularVelocity * -0.01);
   else
      addSpin(angularVelocity * 0.01);
}


/******************************
* SPUTNIK: BREAK APART
* breaks into 4 fragments
***********************************/
void Sputnik::breakApart()
{
   // Create fragments and set their positions and velocities
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
   parts[3] = new Fragment(*this);
}

void Sputnik::draw(ogstream& gout)
{
   if (checkIsCollided())
   { 
      //draw each fragment
      for (int i = 0; i < 4; i++)
         parts[i]->draw(gout); // draw each fragment (part of the sputnik that broke apart
   }
   else
      gout.drawSputnik(getPosition(), getSpin());
}

void Sputnik::moveParts(double time)
{
   for (int i = 0; i < 4; i++) // move all parts of the satellite
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin(); // update the spin of each part
      }
      
}

void Sputnik::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/***************************************************
* GPS METHODS
***************************************************/

void GPS::breakApart()
{
   // Create     pieces and set their positions and velocities
   parts[0] = new GPSCenter(*this);
   parts[1] = new GPSLeft(*this);
   parts[2] = new GPSRight(*this);
}

void GPS::draw(ogstream& gout)
{
   if (checkIsCollided())
   {
      //draw each piece
      for (int i = 0; i < 3; i++)
         parts[i]->draw(gout); // draw each piece (part of the GPS that broke apart)
   }
   else
      gout.drawGPS(getPosition(), getSpin());
}

void GPS::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the GPS
      if (parts[i] != nullptr) // check if part exists
         if (parts[i]->checkIsCollided())
            parts[i]->moveParts(time);
         else
         {
            parts[i]->move(time);
            parts[i]->updateSpin();
         }
      
}

void GPS::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/*****************************************************
* HUBBLE METHODS
*****************************************************/

/***********************************************
* HUBBLE: BREAK APART
* Breaks into 4 Pieces:
* 1. HubbleTelescope
* 2. HubbleComputer
* 3. HubbleLeft
* 4. HubbleRight
*************************************************/
void Hubble::breakApart()
{
   // Create pieces and add them to hubble parts array
   parts[0] = new HubbleTelescope(*this);
   parts[1] = new HubbleComputer(*this);
   parts[2] = new HubbleLeft(*this);
   parts[3] = new HubbleRight(*this);
}

/************************************
* HUBBLE: DRAW
* If collided/broken up, draw each piece, else, draw hubble
************************************/
void Hubble::draw(ogstream& gout)
{
   if (checkIsCollided())
   {
      //draw each piece
      for (int i = 0; i < 4; i++)
         parts[i]->draw(gout); // draw each piece (part of the hubble that broke apart)
   }
   else
      gout.drawHubble(getPosition(), getSpin());
}

/*****************************************
* HUBBLE: MOVE PARTS
* move all four parts
*****************************************/
void Hubble::moveParts(double time)
{
   for (int i = 0; i < 4; i++) // move all parts of the hubble
      if (parts[i] != nullptr) // check if part exists
         if (parts[i]->checkIsCollided())
            parts[i]->moveParts(time);
         else
         {
            parts[i]->move(time);
            parts[i]->updateSpin();
         }
}

void Hubble::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/*****************************************************
* DRAGON METHODS
*****************************************************/

/*************************************
* DRAGON: BREAK APART
* Breaks into 3 pieces and 2 fragments
* Pieces:
* 1. DragonCenter
* 2. DragonLeft
* 3. DragonRight
****************************************/
void Dragon::breakApart()
{
   // Create pieces and add them to dragon parts array
   parts[0] = new DragonCenter(*this);
   parts[1] = new DragonLeft(*this);
   parts[2] = new DragonRight(*this);
   parts[3] = new Fragment(*this);
   parts[4] = new Fragment(*this);
}

/*********************************
* DRAGON: DRAW
* If collided/broken up, draw each piece, else, draw dragon
***********************************/
void Dragon::draw(ogstream& gout)
{
   if (checkIsCollided())
   {
      //draw each piece
      for (int i = 0; i < 5; i++)
         parts[i]->draw(gout); // draw each piece (part of the dragon that broke apart)
   }
   else
      gout.drawCrewDragon(getPosition(), getSpin());
}

/********************************
* DRAGON: MOVE PARTS
* move all five parts
*********************************/
void Dragon::moveParts(double time)
{
   for (int i = 0; i < 5; i++) // move all parts of the dragon
      if (parts[i] != nullptr) // check if part exists
         if (parts[i]->checkIsCollided())
            parts[i]->moveParts(time);
         else
         {
            parts[i]->move(time);
            parts[i]->updateSpin();
         }
}

void Dragon::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/*****************************************************
* STARLINK METHODS
*****************************************************/

/*************************************
* STARLINK: BREAK APART
* Breaks into 2 pieces and 2 fragments
* Pieces:
* 1. StarlinkBody
* 2. StarlinkArray
****************************************/
void Starlink::breakApart()
{
   // Create pieces and add them to starlink parts array
   parts[0] = new StarlinkBody(*this);
   parts[1] = new StarlinkArray(*this);
   parts[2] = new Fragment(*this);
   parts[3] = new Fragment(*this);
}

/*********************************
* STARLINK: DRAW
* If collided/broken up, draw each piece, else, draw starlink
* **********************************/
void Starlink::draw(ogstream& gout)
{
   if (checkIsCollided())
   {
      //draw each piece
      for (int i = 0; i < 4; i++)
         parts[i]->draw(gout); // draw each piece (part of the starlink that broke apart)
   }
   else
      gout.drawStarlink(getPosition(), getSpin());
}

/********************************
* STARLINK: MOVE PARTS
* move all four parts
* *********************************/
void Starlink::moveParts(double time)
{
   for (int i = 0; i < 4; i++) // move all parts of the starlink
      if (parts[i] != nullptr) // check if part exists
         if (parts[i]->checkIsCollided())
            parts[i]->moveParts(time);
         else
         {
            parts[i]->move(time);
            parts[i]->updateSpin();
         }
}

void Starlink::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}


//Other Piece subclass breakApart methods

void Piece::kick()
{
   //random angle between 0 and 360
   Angle newAngle(random(-360, 360));
   //add random velocity to speed between 5000 and 9000 m/s
   double newSpeed = random(5000, 9000) * 0.25;
   Velocity v = getVelocity();
   double dx = newSpeed * sin(newAngle.getRadians());
   double dy = newSpeed * cos(newAngle.getRadians());
   v.addDX(dx);
   v.addDY(dy);
   setVelocity(v);
   //update position
   double newX = getPosition().getPixelsX() + v.getDX() * 0.004 + 0.5 * 1 * pow(0.004, 2);
   double newY = getPosition().getPixelsY() + v.getDY() * 0.004 + 0.5 * 1 * pow(0.004, 2);
   setPositionPixels(newX, newY);
}

/*GPS PARTS*/

void GPSCenter::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void GPSCenter::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void GPSCenter::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void GPSLeft::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void GPSLeft::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void GPSLeft::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void GPSRight::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void GPSRight::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void GPSRight::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/*HUBBLE PIECES*/
void HubbleTelescope::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void HubbleTelescope::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void HubbleTelescope::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void HubbleComputer::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
}

void HubbleComputer::moveParts(double time)
{
   for (int i = 0; i < 2; i++) // move all parts
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}  

void HubbleComputer::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void HubbleRight::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
}

void HubbleRight::moveParts(double time)
{
   for (int i = 0; i < 2; i++) // move all parts of the small piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void HubbleRight::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void HubbleLeft::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
}

void HubbleLeft::moveParts(double time)
{
   for (int i = 0; i < 2; i++) // move all parts of the small piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void HubbleLeft::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}


/*DRAGON PIECES*/ 

void DragonCenter::breakApart()
{
   cout << "GiantPiece breakApart" << endl; //for debuggins
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
   parts[3] = new Fragment(*this);
}

void DragonCenter::moveParts(double time)
{
   for (int i = 0; i < 4; i++) // move all parts of the giant piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void DragonCenter::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void DragonLeft::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
}

void DragonLeft::moveParts(double time)
{
   for (int i = 0; i < 2; i++) // move all parts of the small piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void DragonLeft::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void DragonRight::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
}

void DragonRight::moveParts(double time)
{
   for (int i = 0; i < 2; i++) // move all parts of the small piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void DragonRight::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

/*STARLINK PIECES*/
void StarlinkBody::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void StarlinkBody::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void StarlinkBody::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}

void StarlinkArray::breakApart()
{
   parts[0] = new Fragment(*this);
   parts[1] = new Fragment(*this);
   parts[2] = new Fragment(*this);
}

void StarlinkArray::moveParts(double time)
{
   for (int i = 0; i < 3; i++) // move all parts of the big piece
      if (parts[i] != nullptr) // check if part exists
      {
         parts[i]->move(time);
         parts[i]->updateSpin();
      }
}

void StarlinkArray::checkPartsCollisions(Orbiter& orbiter)
{
   for (int i = 0; i < arraySize; i++)
   {
      if (parts[i]->checkIsCollided())
         parts[i]->checkPartsCollisions(orbiter);
      else
      {
         if (computeDistance(parts[i]->getPosition(), orbiter.getPosition()) < (parts[i]->getRadiusMeters() + orbiter.getRadiusMeters()))
         {
            parts[i]->collide();
            orbiter.collide();
         }
      }
   }
}



