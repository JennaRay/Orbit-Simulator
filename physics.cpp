/*****************************************
* All the physics we need for the prototype
******************************************/

#include <iostream>
#include <cmath>

#define geoDistance 42,164,000.0; // distance from earth to satellite in meters
#define M_PI 3.14159265358979323846

using namespace std;

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