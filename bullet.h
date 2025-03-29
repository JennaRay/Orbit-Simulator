#pragma once
#include "orbiter.h"

class Bullet : public Orbiter
{
public:
	Bullet(const Orbiter& parent)
	{
		Position pos = parent.getPosition();
		Velocity v = parent.getVelocity();

		// Set the position and velocity
		pos.addPixelsX(20 * cos(parent.getAngle().getRadians()));
		pos.addPixelsY(20 * sin(parent.getAngle().getRadians()));
		v.addDX(1000 * cos(parent.getAngle().getRadians()));
		v.addDY(1000 * sin(parent.getAngle().getRadians()));

		setPosition(pos);
		setVelocity(v);
		setAngle(parent.getAngle());
		setRadius(2); // set the bullet radius to 2 pixels so that it can collide (like spaceplane)
		expireTime = 0;
	}

	void move(double time) override {
		Orbiter::move(time);
		expireTime--;
		if (expireTime <= 0)
			setCollide(true);
	}

	void draw(ogstream& gout) override { gout.drawProjectile(getPosition()); }

private: 
	int expireTime;
};