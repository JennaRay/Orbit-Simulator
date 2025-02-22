/*****************************************
* All the physics we need for the prototype
******************************************/

#include <iostream>
#include <cmath>

#define geoDistance 42,164,000.0; // distance from earth to satellite in meters
#define M_PI 3.14159265358979323846

using namespace std;

//Earth equations from the directions

/*********************************************
* GET ROTATION SPEED
rf = -(2 pi / frameRate) x (td / secondsDay)

    rf = rotation of the earth in radians
    for one frame
    frameRate = number of frames per second.
    30 frames per second in our case
    td = how much faster time
    passes in the simulator
    than in the real world
    secondsDay = number of seconds
    for the earth
    to make one rotation
*************************************************/
double getRotationSpeed(double frameRate, double td)
{
   return -(2 * M_PI / frameRate) * (td / 86400.0);
}

/*********************************************
* GET GRAVITY
* gh = g * (r/r+h)^2
*
    gh = magnitude of acceleration due to gravity at an altitude (h)
    g = gravity at sea level: 9.80665 m/s2
    r = radius of the earth: 6,378,000 m
    h = height above the earth in meters
*************************************************/
double getGravity(double h)
{
   double g = 9.80665;
   double r = 6378000;
   return g * pow(r / (r + h), 2);
}

/*********************************************
* GET HEIGHT ABOVE EARTH
* h = √ (x^2 + y^2) - r
*
    h = height above the earth in meters
    x = horizontal position of the satellite where the center of the earth is 0
    y = vertical position of the satellite where the center of the earth is 0
    r = radius of the earth: 6,378,000 m
*************************************************/
double getHeightAboveEarth(double x, double y)
{
   double r = 6378000;
   return sqrt(pow(x, 2) + pow(y, 2)) - r;
}

/*********************************************
* GET DIRECTION OF GRAVITY PULL
* d = atan(xe - xs, ye - ys)
*
    d = direction of the pull of gravity, in radians
    xe = horizontal position of the center of the earth: 0 m
    ye = vertical position of the center of the earth: 0 m
    xs = horizontal position of the satellite in meters
    ys = vertical position of the satellite in meters
*************************************************/
double getDirectionOfGravityPull(double x, double y)
{
   return atan2(y, x);
}

/*********************************************
* GET HORIZONTAL COMPONENT OF ACCELERATION
* ddx = a sin(angle)
*
    ddx = horizontal component of acceleration
    a = total acceleration
    angle = angle (0° is up) of the direction of acceleration
*************************************************/
double getHorizontalComponentOfAcceleration(double a, double angle)
{
   return a * sin(angle);
}

/*********************************************
* GET VERTICAL COMPONENT OF ACCELERATION
* ddy = a cos(angle)
*
    ddy = vertical component of acceleration
    a = total acceleration
    angle = angle (0° is up) of the direction of acceleration
    *************************************************/
double getVerticalComponentOfAcceleration(double a, double angle)
{
   return a * cos(angle);
}

// Motion equations