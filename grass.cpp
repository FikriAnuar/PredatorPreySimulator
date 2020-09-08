//This is the file grass.cpp.
//This is the implementation for the class Grass.
//The interface for the class Grass is in
//the header file grass.h.
#include <iostream>
#include "grass.h"
using std::cout;
Grass::Grass() : Common()
{
	numOfGrasses++;
}
Grass::Grass(World *worldPtr, int X, int Y) : Common(worldPtr,X,Y)
{
	numOfGrasses++;
}
void Grass::move()
{/*Grass does not move. Intentionally blank.*/}
void Grass::breed()
{/*Grass does not breed. Intentionally blank.*/}
int Grass::getType() const
{
	return 5;
}
int Grass::numOfGrasses = 0;
Grass::~Grass()
{
	numOfGrasses--;
}

