#include <iostream>
#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include "angle.h"
#include "orbiter.h"
#include "satellite.h"
#include "simulator.h"

void Simulator::display(ogstream& gout)
{
   //display earth
   gout.drawEarth(earthPos, angleEarth.getRadians());

   //display satellites
   sputnik.draw(gout);
   gps1.draw(gout);
   gps2.draw(gout);
   gps3.draw(gout);
   gps4.draw(gout);
   gps5.draw(gout);
   gps6.draw(gout);
   hubble.draw(gout);
   dragon.draw(gout);
   starlink.draw(gout);
}

void Simulator::moveOrbiters()
{
   sputnik.move(time);
   gps1.move(time);
   gps2.move(time);
   gps3.move(time);
   gps4.move(time);
   gps5.move(time);
   gps6.move(time);
   hubble.move(time);
   dragon.move(time);
   starlink.move(time);
}