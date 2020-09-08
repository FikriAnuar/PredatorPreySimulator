//This is the header file tiger.h.
//This is the interface for the class Tiger.
#ifndef TIGER_H
#define TIGER_H
#include "common.h"
#include <iostream>
using std::cout;
class Tiger : public Common
{
friend class World;
friend class Rabbit;
friend class Grass;
public:
	Tiger(); //Default constructor
	Tiger(World *worldPtr, int X, int Y);
	void move();
	void breed();
	int getType() const;
	static int numOfTigers;
	static int numBorn;
	static int numStarve;
	static int numCaptured;
	static int numFall;
	~Tiger();
};
#endif //TIGER_H
