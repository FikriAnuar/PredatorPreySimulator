//This is the header file pit.h.
//This is the interface for the class Pit.
#ifndef PIT_H
#define PIT_H
#include "common.h"
#include <iostream>
using std::cout;
class Pit : public Common
{
friend class World;
public:
	Pit();
	Pit(World *worldPtr, int X, int Y);
	void move();
	void breed();
	int getType() const;
	static int numOfPits;
	~Pit();
};
#endif //PIT_H
