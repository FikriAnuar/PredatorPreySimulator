//This is the file rabbit.cpp.
//This is the implementation for the class Rabbit.
//The interface for the class Rabbit is in
//the header file rabbit.h.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "rabbit.h"
#include "grass.h"
#include "world.h"
using std::cout;
Rabbit::Rabbit() : Common()
{
	numBorn++;
	numOfRabbits++;
}
Rabbit::Rabbit(World *worldPtr, int X, int Y) : Common(worldPtr,X,Y)
{
	numBorn++;
	numOfRabbits++;
}
void Rabbit::move()
{//Searches rabbit's surrounding area for grass. The rabbit will eat a random available grass or move to an empty space if there are no available grasses or stay in the same position if there are no available spaces to move.
	bool grassAvailable = true, leftGrass = true, rightGrass = true, upGrass = true, downGrass = true;
	while ((movement == false) && (grassAvailable == true))
	{
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->getObject(x, y-1) != NULL) && (world->getObject(x, y-1)->getType() == GRASS)) //Left grass availability
			{
				delete (world->worldMap[x][y-1]);
				world->worldMap[x][y-1] = this;
				world->createObject(x, y, NULL);
				bool grassCreated = false;
				while (grassCreated == false)
				{
					int x = (rand()%WORLDSIZE);
					int y = (rand()%WORLDSIZE);	
					if (world->getObject(x, y) == NULL)
					{	
						Grass *newGrass = new Grass(world,x,y);
						world->createObject(x, y, newGrass);
						grassCreated = true;
					}	
				}
				movement = true;
				stamina = STARVE;
				lifetime++;
				y--;
			}
			else
				leftGrass = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->getObject(x, y+1) != NULL) && (world->getObject(x, y+1)->getType() == GRASS)) //Right grass availability
			{
				delete (world->worldMap[x][y+1]);
				world->worldMap[x][y+1] = this;
				world->createObject(x, y, NULL);
				bool grassCreated = false;
				while (grassCreated == false)
				{
					int x = (rand()%WORLDSIZE);
					int y = (rand()%WORLDSIZE);	
					if (world->getObject(x, y) == NULL)
					{	
						Grass *newGrass = new Grass(world,x,y);
						world->createObject(x, y, newGrass);
						grassCreated = true;
					}	
				}
				movement = true;
				stamina = STARVE;
				lifetime++;
				y++;
			}
			else rightGrass = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->getObject(x-1, y) != NULL) && (world->getObject(x-1,y)->getType() == GRASS)) //Up grass availability
			{
				delete (world->worldMap[x-1][y]);
				world->worldMap[x-1][y] = this;
				world->createObject(x, y, NULL);
				bool grassCreated = false;
				while (grassCreated == false)
				{
					int x = (rand()%WORLDSIZE);
					int y = (rand()%WORLDSIZE);	
					if (world->getObject(x, y) == NULL)
					{	
						Grass *newGrass = new Grass(world,x,y);
						world->createObject(x, y, newGrass);
						grassCreated = true;
					}	
				}
				movement = true;
				stamina = STARVE;
				lifetime++;
				x--;
			}
			else upGrass = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 1) && (world->getObject(x+1, y) != NULL) && (world->getObject(x+1,y)->getType() == GRASS)) //Down grass availability
			{
				delete (world->worldMap[x+1][y]);
				world->worldMap[x+1][y] = this;
				world->createObject(x, y, NULL);
				bool grassCreated = false;
				while (grassCreated == false)
				{
					int x = (rand()%WORLDSIZE);
					int y = (rand()%WORLDSIZE);	
					if (world->getObject(x, y) == NULL)
					{	
						Grass *newGrass = new Grass(world,x,y);
						world->createObject(x, y, newGrass);
						grassCreated = true;
					}	
				}
				movement = true;
				stamina = STARVE;
				lifetime++;
				x++;
			}
			else downGrass = false;
		}
		if ((leftGrass == false) && (rightGrass == false) && (upGrass == false) && (downGrass == false))
			grassAvailable = false;
	}
	if (movement == false) //Rabbit moves to an empty space or pit if it did not eat a grass or stays in same location if the space is taken or off the grid.
	{
		int direction (rand()%4);
		if (direction == 0) //Moves rabbit left if available.
		{
			if ((y > 0) && ((world->getObject(x,y-1) == NULL) || ((world->getObject(x,y-1) != NULL ) && (world->getObject(x,y-1)->getType() == PIT))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x,y-1) == NULL)
				{
					world->worldMap[x][y-1] = this;
					world->createObject(x, y, NULL);
					y--;
				}
				else //If moves to a pit.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		else if (direction == 1) //Moves rabbit right if available.
		{
			if ((y < WORLDSIZE -1) && ((world->getObject(x,y+1) == NULL) || ((world->getObject(x,y+1) != NULL ) && (world->getObject(x,y+1)->getType() == PIT))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x,y+1) == NULL)
				{
					world->worldMap[x][y+1] = this;
					world->createObject(x, y, NULL);
					y++;
				}
				else //If moves to a pit.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		} 
		else if (direction == 2) //Moves rabbit up if available.
		{
			if ((x > 0) && ((world->getObject(x-1,y) == NULL) || ((world->getObject(x-1,y) != NULL ) && (world->getObject(x-1,y)->getType() == PIT))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x-1,y) == NULL)
				{
					world->worldMap[x-1][y] = this;
					world->createObject(x, y, NULL);
					x--;
				}
				else //If moves to a pit.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		else if (direction == 3) //Moves rabbit down if available.
		{
			if ((x < WORLDSIZE -1) && ((world->getObject(x+1,y) == NULL) || ((world->getObject(x+1,y) != NULL ) && (world->getObject(x+1,y)->getType() == PIT))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x+1,y) == NULL)
				{
					world->worldMap[x+1][y] = this;
					world->createObject(x, y, NULL);
					x++;
				}
				else //If moves to a pit.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		stamina--;
		lifetime++;
	}
}
void Rabbit::breed()
{
	bool bred = false, leftSpace = true, rightSpace = true, upSpace = true, downSpace = true;
	while (bred == false)
	{
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->worldMap[x][y-1] == NULL)) //Left space availability
			{
				Rabbit *newRabbit = new Rabbit(world,x,y-1);
				world->createObject(x, y-1, newRabbit);
				bred = true;
			}
			else
				leftSpace = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->worldMap[x][y+1] == NULL)) //Right space availability
			{
				Rabbit *newRabbit = new Rabbit(world,x,y+1);
				world->createObject(x, y+1, newRabbit);
				bred = true;
			}
			else rightSpace = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->worldMap[x-1][y] == NULL)) //Up space availability
			{
				Rabbit *newRabbit = new Rabbit(world,x-1,y);
				world->createObject(x-1, y, newRabbit);
				bred = true;
			}
			else upSpace = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 1) && (world->worldMap[x+1][y] == NULL)) //Down space availability
			{
				Rabbit *newRabbit = new Rabbit(world,x+1,y);
				world->createObject(x+1, y, newRabbit);
				bred = true;
			}
			else downSpace = false;
		}
		if ((leftSpace == false) && (rightSpace == false) && (upSpace == false) && (downSpace == false))
		{
			bred = true;
		}
	}
}
int Rabbit::getType() const
{
	return 1;
}
int Rabbit::numOfRabbits = 0;
int Rabbit::numBorn = 0;
int Rabbit::numStarve = 0;
int Rabbit::numCaptured = 0;
int Rabbit::numFall = 0;
Rabbit::~Rabbit()
{
	numOfRabbits--;
}
