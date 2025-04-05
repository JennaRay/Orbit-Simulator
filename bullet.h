#pragma once
#include "orbiter.h"
#include "spaceplane.h"

class Bullet : public Orbiter
{
public:
	Bullet(Orbiter& parent, double thrust)
	{
		Position pos = parent.getPosition();
		Velocity v = parent.getVelocity();

		// Set the position and velocity
		pos.addPixelsX(20 * sin(parent.getSpin()));
		pos.addPixelsY(20 * cos(parent.getSpin()));
		v.addDX(((thrust/10) + 9000) * sin(parent.getSpin()));
		v.addDY(((thrust/10) + 9000) * cos(parent.getSpin()));

		setPosition(pos);
		setVelocity(v);
		Angle newAngle = Angle(parent.getSpin());
		setAngle(newAngle);
		setRadius(1); // set the bullet radius to 2 pixels so that it can collide (like spaceplane)
		expireTime = 70;
		expireCount = 0;
      setCollide(false);
	}
	void collide() override
	{
		setCollide(true);
	}
	void moveForward(double time)
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

	void draw(ogstream& gout) override
	{
		if (expireCount < expireTime && not checkIsCollided()) // Only draw if not expired or collided - need to add collide check
			gout.drawProjectile(getPosition());
	}

private: 
	int expireTime;
	int expireCount;
};