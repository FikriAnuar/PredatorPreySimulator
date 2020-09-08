//This is the file common.cpp.
//This is the implementation for the class Common.
//The interface for the class Common is in
//the header file common.h.
#include <iostream>
#include "common.h"
using std::cout;
Common::Common() //Default constructor.
{
	x = -1;
	y = -1;
	lifetime = 0;
	stamina = 0;
	movement = false;
	world = NULL;
}
Common::Common(World *worldPtr, int X, int Y) //Main base constructor for all derived classes.
{
	x = X;
	y = Y;
	lifetime = 0;
	stamina = STARVE;
	movement = false;
	world = worldPtr;
}
Common::~Common()
{
}
