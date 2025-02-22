#pragma once

#include <iostream>
#include <cmath>
#include "position.h"

#define M_PI 3.14159265358979323846

using namespace std;

// TIME CONSTANTS
constexpr int secondsMinute = 60;
constexpr int minutesHour = 60;
constexpr int hoursDay = 24;
constexpr int frameRate = 30;
constexpr int secondsDay = hoursDay * minutesHour * secondsMinute; // 86400 seconds / day

// EARTH CONSTANTS
constexpr double geoDistance = 42164000.0; // Distance from Earth to satellite in meters
constexpr double geoSpeed = 3100.0; // Speed of satellite in m/s
constexpr double g = 9.80665; // Gravitational acceleration (m/s^2)
constexpr double r = 6378000.0; // Radius of Earth in meters

double getGeoDistance()
{
   return 42164000.0;
}
double getGeoSpeed()
{
   return 3100.0;
}
// Time equations from the directions

/***************************************
* GET TIME DILATION
* Equation: td = hoursDay x minutesHour
***************************************/
double getTd(int hoursDay, double minutesHour) {
   double td = hoursDay * minutesHour;

   return td;
}

/********************************
* GET TIME PER FRAME
* Equation: tpf = td / frameRate
********************************/
double getTpf(double td, int frameRate) {
   return td / frameRate;
}


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

/*************************************************
* NEWTON's FIRST LAW
* Equation: st = s0
*
* s denotes a location that is expressed in
* two dimensions (in an x, y coordinate plane)
*
* st = distance at a given time t.
*      (This is a position on a coordinate plane)
* s0 = initial position
*************************************************/
double newtonsFirstLaw(double s0)
{
   return s0;
}

/*******************************
* MOTION WITH CONSTANT VELOCITY
* Equation: s = s0 + vt
*
* s = distance in meters (m)
* s0 = initial distance (m)
* v = velocity (m/s)
* t = time (s)
*******************************/
double motionConstantVelocity(double s0, double v, double t)
{

   return s0 + (v * t);
}

/**********************************************
* HORIZONTAL POSITION CONSTANT VELOCITY
* Equation: xt = x0 + dx t
*
* x = horizontal position at time t (m)
* x0 = initial horizontal position (m)
* dx = horizontal component of velocity (m/s)
* t = time (s)
**********************************************/
double hPosConstantVelocity(double x0, double dx, double t)
{
   return x0 + (dx * t);
}

/**********************************************
* VERTICAL POSITION CONSTANT VELOCITY
* Equation: xt = x0 + dx t
*
* y = vertical position at time t (m)
* y0 = initial vertical position (m)
* dx = vertical component of velocity (m/s)
* t = time (s)
**********************************************/
double vPosConstantVelocity(double y0, double yx, double t)
{
   return y0 + (yx * t);
}

/*********************************************
* GET DISTANCE
* s = s0 + v t + ½ a t^2
*
    s = distance in meters (m)
    s0 = initial distance (m)
    v = velocity (m/s)
    t = time (s)
    a = acceleration (m/s2)
*************************************************/
double getDistance(double s0, double v, double t, double a)
{
   return s0 + v * t + 0.5 * a * pow(t, 2);
}

/*********************************************
* GET VELOCITY
* v = v0 + a t
*
*
    v = velocity in meters (m/s)
    v0 = initial velocity (m/s)
    a = acceleration (m/s2)
    t = time (s)
*************************************************/
double getVelocity(double v0, double a, double t)
{
   return v0 + a * t;
}

/*********************************************
* GET DISTANCE COMPONENT
* use to get horizontal distance or vertical distance
* xt = x0 + dx t + ½ ddx t^2
*
    xt = horizontal position at time t (m)
    x0 = initial horizontal position (m)
    dx = horizontal component of velocity (m/s)
    ddx = horizontal component of acceleration (m/s2)
    t = time (s)
*******************************************************/
double getDistanceComponent(double x0, double dx, double t, double ddx)
{
   return x0 + dx * t + 0.5 * ddx * pow(t, 2);
}

/*********************************************
* GET VELOCITY COMPONENT
* use to get horizontal velocity or vertical velocity
* dxt = dx0 + ddx t
*
    dxt = horizontal velocity at time t (m/s)
    dx0 = initial horizontal velocity (m/s)
    ddx = horizontal component of acceleration (m/s2)
    t = time (s)
*******************************************************/
double getVelocityComponent(double dx0, double ddx, double t)
{
   return dx0 + ddx * t;
}

/*********************************************
* MOVE PROTOTYPE
* completel one loop of the calculations to move 
* the prototype in orbit
***********************************************/
void movePrototype(Position& PTpos, double& angle, double& v, double& t)
{
   double x = PTpos.getMetersX();
   double y = PTpos.getMetersY();

   // figure out acceleration (we already have gravity defined above)
   double gn = getGravity(y);
   double ddx = getHorizontalComponentOfAcceleration(gn, angle);
   double ddy = getVerticalComponentOfAcceleration(gn, angle);
   
   // figure out velocity
   double newV = getVelocity(v, angle, t);
   v = newV;
   // gonna use these functions bc I'm pretty sure the math should work for velocity to
   double dx = getHorizontalComponentOfAcceleration(newV, angle);
   double dy = getVerticalComponentOfAcceleration(newV, angle);

   // figure out new distance maybe is next?
   double newX = getDistanceComponent(x, dx, t, ddx);
   double newY = getDistanceComponent(y, dy, t, ddy);
   PTpos.setMeters(newX, newY);
}