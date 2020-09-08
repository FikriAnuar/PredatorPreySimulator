//This is the header file rabbit.h.
//This is the interface for the class Rabbit.
#ifndef RABBIT_H
#define RABBIT_H
#include "common.h"
#include <iostream>
using std::cout;
class Rabbit : public Common
{
friend class World;
friend class Grass;
public:
	Rabbit();
	Rabbit(World *worldPtr, int X, int Y);
	void move();
	void breed();
	int getType() const;
	static int numOfRabbits;
	static int numBorn;
	static int numStarve;
	static int numCaptured;
	static int numFall;
	~Rabbit();
};
#endif //RABBIT_H
