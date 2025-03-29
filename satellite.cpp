#pragma once
#include "satellite.h"

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