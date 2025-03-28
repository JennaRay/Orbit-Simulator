/*************************************************************
 * 1. Name:
 *      William Torman and Jenna Ray
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 *      https://youtu.be/U7ZLDh7L8f0
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      We could not figure out how to get the satellite to properly orbit.
 * 5. How long did it take for you to complete the assignment?
 *      9 Hours
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "test.h"
#include "simulator.h"
using namespace std;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   //Demo* pDemo = (Demo*)p;
   Simulator* sim = (Simulator*)p;

   Position pt;
   ogstream gout(pt);

   //do stuff for stars

   //move things in orbit
   sim->moveOrbiters();
   sim->rotateEarth();

   //check for collisions
   sim->checkCollisions();

   //accept input and move ship based on it
   sim->handleInput(pUI);
   sim->movePlane();
   //draw everything
   sim->display(gout);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Orbit Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the simulator
   Simulator sim(ptUpperRight);
   // set everything into action
   //ui.run(callBack, &demo);
   ui.run(callBack, &sim);


   return 0;
}
