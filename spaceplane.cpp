#include <iostream>
#include "spaceplane.h"

using namespace std;

/*************************************
* MOVEFORWARD
* Move the spaceplane in the direction its facing
****************************************/

void SpacePlane::moveForward()
{
   double a = getSpin();
   double ax = thrust * sin(a);
   double ay = thrust * cos(a);


   Velocity v = getVelocity();
   v.setDX(v.getDX() + ax * TIME_STEP);
   v.setDY(v.getDY() + ay * TIME_STEP);

   Position pos = getPosition();
   double newX = pos.getMetersX() + v.getDX() * TIME_STEP + 0.5 * thrust * pow(TIME_STEP, 2);
   double newY = pos.getMetersY() + v.getDY() * TIME_STEP + 0.5 * thrust * pow(TIME_STEP, 2);

   setPosition(newX, newY);
}

/*******************************
* Move BULLETS
* Move all bullets on the screen
*******************************/
void SpacePlane::moveBullet(double time) {
	// .begin() is the 1st element in the vector and .end() is last
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		it->moveForward(time);
		//if (it->checkIsCollided()) // check collision
		//	it = bullets.erase(it); // if collided, erase
	}
}

/*************************************
* DRAW BULLETS
* Draw all bullets on the screen
****************************************/
void SpacePlane::drawBullets(ogstream& gout)
{
	for (auto& bullet : bullets)
		bullet.draw(gout);
}

/*************************************
* DRAW BULLET
* Draw a single bullet on the screen
****************************************/
void SpacePlane::drawBullet(ogstream& gout)
{
	for (auto& bullet : bullets)
		bullet.draw(gout);
}

/*************************************
* CHECK BULLET COLLISIONS
* check if any bullets have collided
*************************************/
void SpacePlane::checkBulletCollisions(Orbiter& orbiter)
{
   for (auto it = bullets.begin(); it != bullets.end(); )
   {  
      if (not it->checkIsCollided())
      {
         it = bullets.erase(it); // erase the bullet if it has collided
         continue; // skip to the next iteration
      }
      if (computeDistance(it->getPosition(), orbiter.getPosition()) < (it->getRadiusMeters() + orbiter.getRadiusMeters()))
      {
         // If the bullet collides with the orbiter
         orbiter.collide(); // call collide on the orbiter
         it->collide(); // erase the bullet after collision

      }
      else
      {
         ++it; // move to the next bullet
      }
   }
}