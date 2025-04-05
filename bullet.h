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
		v.addDX(((thrust/4) + 9000) * sin(parent.getSpin()));
		v.addDY(((thrust/4) + 9000) * cos(parent.getSpin()));

		setPosition(pos);
		setVelocity(v);
		Angle newAngle = Angle(parent.getSpin());
		setAngle(newAngle);
		setRadius(2); // set the bullet radius to 2 pixels so that it can collide (like spaceplane)
		expireTime = 100;
      setCollide(false);
	}
	void collide() override
	{
		setCollide(true);
	}
	void moveForward(double time) {

		Position pos = getPosition();
		double newX = pos.getMetersX() + getVelocity().getDX() * time + 0.5 * 1 * pow(time, 2);
		double newY = pos.getMetersY() + getVelocity().getDY() * time + 0.5 * 1 * pow(time, 2);

		setPosition(newX, newY);

		//expireTime--;
		/*if (expireTime <= 0)
			setCollide(true);*/

	}

	void draw(ogstream& gout) override { gout.drawProjectile(getPosition()); }

private: 
	int expireTime;
};