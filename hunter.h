//This is the header file hunter.h.
//This is the interface for the class Hunter.
#ifndef HUNTER_H
#define HUNTER_H
#include "common.h"
#include <iostream>
using std::cout;
class Hunter : public Common
{
friend class World;
friend class Rabbit;
friend class Tiger;
friend class Grass;
public:
	Hunter();
	Hunter(World *worldPtr, int X, int Y);
	void move();
	void breed();
	int getType() const;
	static int numOfHunters;
	static int numBorn;
	static int numStarve;
	static int numCaptured;
	static int numFall;
	~Hunter();
};
#endif //HUNTER_H
