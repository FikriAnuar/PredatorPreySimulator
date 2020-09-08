//This is the header file grass.h.
//This is the interface for the class Grass.
#ifndef GRASS_H
#define GRASS_H
#include "common.h"
#include <iostream>
using std::cout;
class Grass : public Common
{
friend class World;
public:
	Grass();
	Grass(World *worldPtr, int X, int Y);
	void move();
	void breed();
	int getType() const;
	static int numOfGrasses;
	~Grass();
};
#endif //GRASS_H
