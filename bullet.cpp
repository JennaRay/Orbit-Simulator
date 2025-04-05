#include "bullet.h"

using namespace std;

void Bullet::moveForward(double time) 
{

   Position pos = getPosition();
   double newX = pos.getMetersX() + getVelocity().getDX() * time + 0.5 * 1 * pow(time, 2);
   double newY = pos.getMetersY() + getVelocity().getDY() * time + 0.5 * 1 * pow(time, 2);

   setPosition(newX, newY);

   expireCount += 1;
   if (expireCount >= expireTime) {
      // If the bullet has expired, mark it as collided
      collide();
      // Optionally, you could also remove it from the game or set its position to an invalid state
      // For now, we just mark it as collided
   }
}

void Bullet::draw(ogstream& gout)
{
   if (expireCount < expireTime) // Only draw if not expired or collided - need to add collide check
      gout.drawProjectile(getPosition());
}