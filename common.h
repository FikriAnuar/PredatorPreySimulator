//This is the header file common.h.
//This is the interface for the class Common.
//This is primarily intended to be used as a base class to derive
//classes for different kinds of objects.
#ifndef COMMON_H
#define COMMON_H
#include "world.h"
#include <iostream>
using std::cout;
class Common
{
friend class World; //Allows Common to use World member functions and variables.
public:
	Common(); //Default constructor.
	Common(World *worldPtr, int X, int Y); //Constructor that sets coordinates based on arguments.
	virtual void move() = 0; //Used for move method on derived classes.
	virtual void breed() = 0; //Used for breeding method on derived classes.
	virtual int getType() const = 0; //Used to return the type of object (i.e. Rabbit is type 1).
	virtual ~Common(); //Destructor.
protected:
	int x; //X-coordinate
	int y; //Y-coordinate
	int lifetime; //Represents how many steps the object has lived.
	int stamina; //Represents how many steps until the object will starve.
	bool movement; //Represents whether the object moved during the current step.
	World *world; //Points the object to the location on the world map.
};
#endif //COMMON_H
