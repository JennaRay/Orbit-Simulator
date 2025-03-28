#pragma once

/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159
#define TWO_PI 6.28318530718

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestOrbiter;
class TestSpacePlane;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
   friend TestVelocity;
   friend TestAngle;
   friend TestAcceleration;
   friend TestOrbiter;
   friend TestSpacePlane;

   // Constructors
   Angle() : radians(0.0) {}
   Angle(const Angle& rhs) : radians(rhs.radians) {}
   Angle(double degrees) : radians(degrees* M_PI / 180.0) {}

   // Getters
   double getDegrees() { return convertToDegrees(radians); }
   double getRadians() const { return radians; }

   // Setters
   void setDegrees(double d) { radians = normalize(convertToRadians(d)); };
   void setRadians(double r) { radians = normalize(r); };
   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }          // 180° in radians
   void setRight() { radians = M_PI / 2.0; }    // 90° in radians
   void setLeft() { radians = 3 * M_PI / 2.0; }// 270° in radians
   void reverse() { radians += M_PI; normalize(radians); }
   Angle& add(double delta) { radians += delta; radians = normalize(radians); return *this; }

private:
   double radians;   // 360 degrees equals 2 PI radians

   double normalize(double r)
   {
      double normalized = fmod(r, TWO_PI);

      if (normalized < 0) {
         normalized += TWO_PI;
      }

      return normalized;
   };
   double convertToDegrees(double r)
   {
      return normalize(radians) * (180 / M_PI);
   };
   double convertToRadians(double d)
   {
      return normalize(d * (M_PI / 180));
   };
   double normalize(double r) const;
};