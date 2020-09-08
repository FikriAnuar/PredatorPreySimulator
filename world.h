//This is the header file world.h.
//This is the interface for the class World.
#ifndef WORLD_H
#define WORLD_H
#include <iostream>
using namespace std;
const int WORLDSIZE = 20; //Determines the size of the world.

//Used for determining type. Allows for more types of objects if desired.
const int RABBIT = 1;
const int TIGER = 2;
const int HUNTER = 3;
const int PIT = 4;
const int GRASS = 5;

//Used for determining whether a species will breed or not.
const int RABBIT_BREED = 3;
const int TIGER_BREED = 4;
const int HUNTER_BREED = 8;

//Used for determining whether a species will starve or not.
const int STARVE = 3;

class Common;
class Rabbit;
class Tiger;
class Hunter;
class Pit;
class Grass;

class World
{
	friend class Common;
	friend class Rabbit;
	friend class Tiger;
	friend class Hunter;
	friend class Pit;
	friend class Grass;
public:
	World();
	void printStep(); //Displays world and data.
	void resetVariables(); //Resets variables after each step.
	void nextStep(); //Performs next step.
	Common* getObject(int x, int y) const;
	void createObject(int x, int y, Common *theObject);
private:
	Common* worldMap[WORLDSIZE][WORLDSIZE];
};
#endif //WORLD_H
