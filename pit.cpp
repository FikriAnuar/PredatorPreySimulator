//This is the file pit.cpp.
//This is the implementation for the class Pit.
//The interface for the class Pit is in
//the header file pit.h.
#include <iostream>
#include "pit.h"
using std::cout;
Pit::Pit() : Common()
{
	numOfPits++;
}
Pit::Pit(World *worldPtr, int X, int Y) : Common(worldPtr,X,Y)
{
	numOfPits++;
}
void Pit::move()
{/*Pits cannot move. Intentionally blank.*/}
void Pit::breed()
{/*Pits cannot breed. Intentionally blank.*/}
int Pit::getType() const
{
	return 4;
}
int Pit::numOfPits = 0;
Pit::~Pit()
{
	numOfPits--;
	/*Pit count will always remains the same*/
}
