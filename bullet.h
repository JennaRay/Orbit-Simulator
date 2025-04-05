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
	void moveForward(double time);

	void draw(ogstream& gout) override;

private: 
	int expireTime;
	int expireCount;
};