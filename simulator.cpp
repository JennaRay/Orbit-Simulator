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
   sputnik.draw(gout);
}