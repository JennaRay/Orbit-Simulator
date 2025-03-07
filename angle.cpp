/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
   double normalized = fmod(radians, 2 * M_PI); // Normalize to [0, 2π)

   // If normalized value is negative, adjust it to be in the positive range
   if (normalized < 0) {
      normalized += 2 * M_PI;
   }

   return normalized;
}