//This is the file world.cpp.
//This is the implementation for the class World.
//The interface for the class World is in the
//header file world.h.
#include <iostream>
#include "world.h"
#include "common.h"
#include "rabbit.h"
#include "hunter.h"
#include "tiger.h"
#include "pit.h"
#include "grass.h"
#include <cstdlib>
#include <ctime>
using std::cout;
using namespace std;
World::World()
{
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			worldMap[i][j] = NULL;
}
void World::printStep()
{
	for (int i = 0; i < WORLDSIZE; i++)
	{
		for (int j = 0; j < WORLDSIZE; j++)
		{
			if (getObject(i, j) == NULL)
				cout << "- ";
			else if (getObject(i, j)->getType() == RABBIT)
				cout << "R ";
			else if (getObject(i, j)->getType() == TIGER)
				cout << "T ";
			else if (getObject(i, j)->getType() == HUNTER)
				cout << "H ";
			else if (getObject(i, j)->getType() == GRASS)
				cout << "* ";
			else if (getObject(i, j)->getType() == PIT)
				cout << "O ";
		}
		cout << "\n";
	}
	cout << "Number of Rabbits:\t" << Rabbit::numOfRabbits << "\t <born: " << Rabbit::numBorn << ", starve:" << Rabbit::numStarve << ", captured:" << Rabbit::numCaptured <<", fall:" << Rabbit::numFall << ">\n";
	cout << "Number of Tigers:\t" << Tiger::numOfTigers << "\t <born: " << Tiger::numBorn << ", starve:" << Tiger::numStarve << ", captured:" << Tiger::numCaptured <<", fall:" << Tiger::numFall << ">\n";
	cout << "Number of Hunters:\t" << Hunter::numOfHunters << "\t <born: " << Hunter::numBorn << ", starve:" << Hunter::numStarve << ", captured:" << Hunter::numCaptured <<", fall:" << Hunter::numFall << ">\n";
	cout << "Number of Grasses:\t" << Grass::numOfGrasses << "\n";
	cout << "Number of Pits:\t\t" << Pit::numOfPits << "\n";
}
void World::resetVariables()
{
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				worldMap[i][j]->movement = false;
	Rabbit::numBorn = 0;
	Rabbit::numStarve = 0;
	Rabbit::numCaptured = 0;
	Rabbit::numFall = 0;
	Tiger::numBorn = 0;
	Tiger::numStarve = 0;
	Tiger::numCaptured = 0;
	Tiger::numFall = 0;
	Hunter::numBorn = 0;
	Hunter::numStarve = 0;
	Hunter::numCaptured = 0;
	Hunter::numFall = 0;
}
void World::nextStep()
{
	//Hunter moves.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == HUNTER)
					if (worldMap[i][j]->movement == false)
						worldMap[i][j]->move();
	//Tigers moves.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == TIGER)
					if (worldMap[i][j]->movement == false)
						worldMap[i][j]->move();
	//Rabbit moves.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == RABBIT)
					if (worldMap[i][j]->movement == false)
						worldMap[i][j]->move();
	//All creatures that haven't eaten in a certain number of turns will die.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->stamina == 0)
				{
					if (worldMap[i][j]->getType() == RABBIT)
						Rabbit::numStarve++;
					else if (worldMap[i][j]->getType() == TIGER)
						Tiger::numStarve++;
					else if (worldMap[i][j]->getType() == HUNTER)
						Hunter::numStarve++;
					delete worldMap[i][j];
					createObject(i, j, NULL);
				}
	//Hunter breeds.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == HUNTER)
					if (((worldMap[i][j]->lifetime) != 0) && (((worldMap[i][j]->lifetime) % HUNTER_BREED) == 0))
						worldMap[i][j]->breed();
	//Tiger breeds.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == TIGER)
					if (((worldMap[i][j]->lifetime) != 0) && (((worldMap[i][j]->lifetime) % TIGER_BREED) == 0))
						worldMap[i][j]->breed();
	//Rabbit breeds.
	for (int i = 0; i < WORLDSIZE; i++)
		for (int j = 0; j < WORLDSIZE; j++)
			if (worldMap[i][j] != NULL)
				if (worldMap[i][j]->getType() == RABBIT)
					if (((worldMap[i][j]->lifetime) != 0) && (((worldMap[i][j]->lifetime) % RABBIT_BREED) == 0))
						worldMap[i][j]->breed();
}
Common* World::getObject(int x, int y) const
{
	if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE))
		return worldMap[x][y];
	else
		return NULL; //Accounts for out-of-bounds coordinates.
}
void World::createObject(int x, int y, Common *theObject)
{
	worldMap[x][y] = theObject;
}
