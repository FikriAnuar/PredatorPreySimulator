//This is the file tiger.cpp.
//This is the implementation for the class Tiger.
//The interface for the class Tiger is in
//the header file tiger.h.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tiger.h"
#include "rabbit.h"
#include "grass.h"
#include <iostream>
using std::cout;
Tiger::Tiger() : Common()
{
	numBorn++;
	numOfTigers++;
}
Tiger::Tiger(World *worldPtr, int X, int Y) : Common(worldPtr,X,Y)
{
	numBorn++;
	numOfTigers++;
}
void Tiger::move()
{//Searches tiger's surrounding area for rabbit. The tiger will eat a random available rabbit or move to an empty space if there are no available rabbits or stay in the same position if there are no available spaces to move.
	bool rabbitAvailable = true, leftRabbit = true, rightRabbit = true, upRabbit = true, downRabbit = true;
	while ((movement == false) && (rabbitAvailable == true))
	{	
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->getObject(x, y-1) != NULL) && (world->getObject(x, y-1)->getType() == RABBIT)) //Left rabbit availability
			{
				delete (world->worldMap[x][y-1]);
				world->worldMap[x][y-1] = this;
				world->createObject(x, y, NULL);
				movement = true;
				Rabbit::numCaptured++;
				stamina = STARVE;
				lifetime++;
				y--;
			}
			else
				leftRabbit = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->getObject(x, y+1) != NULL) && (world->getObject(x, y+1)->getType() == RABBIT)) //Right rabbit availability
			{
				delete (world->worldMap[x][y+1]);
				world->worldMap[x][y+1] = this;
				world->createObject(x, y, NULL);
				movement = true;
				Rabbit::numCaptured++;
				stamina = STARVE;
				lifetime++;
				y++;
			}
			else rightRabbit = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->getObject(x-1, y) != NULL) && (world->getObject(x-1,y)->getType() == RABBIT)) //Up rabbit availability
			{
				delete (world->worldMap[x-1][y]);
				world->worldMap[x-1][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				Rabbit::numCaptured++;
				stamina = STARVE;
				lifetime++;
				x--;
			}
			else upRabbit = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 1) && (world->getObject(x+1, y) != NULL) && (world->getObject(x+1,y)->getType() == RABBIT)) //Down rabbit availability
			{
				delete (world->worldMap[x+1][y]);
				world->worldMap[x+1][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				Rabbit::numCaptured++;
				stamina = STARVE;
				lifetime++;
				x++;
			}
			else downRabbit = false;
		}
		if ((leftRabbit == false) && (rightRabbit == false) && (upRabbit == false) && (downRabbit == false))
			rabbitAvailable = false;
	}
	if (movement == false) //Tiger moves to an empty space or pit or steps on a grass if it did not eat a rabbit or stays in same location if the space is taken or off the grid.
	{	
		int direction (rand()%4);
		if (direction == 0) //Moves tiger left if available.
		{
			if ((y > 0) && ((world->getObject(x,y-1) == NULL) || ((world->getObject(x,y-1) != NULL ) && ((world->getObject(x,y-1)->getType() == PIT) || (world->getObject(x,y-1)->getType() == GRASS)))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x,y-1) == NULL)
				{
					world->worldMap[x][y-1] = this;
					world->createObject(x, y, NULL);
					y--;
				}
				else if (world->getObject(x,y-1)->getType() == GRASS) //If moves on grass. Grass disappears and another re-appears somewhere else.
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
					y--;
				}
				else //If moves to a pit. Tiger falls.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		else if (direction == 1) //Moves tiger right if available.
		{
			if ((y < WORLDSIZE -1) && ((world->getObject(x,y+1) == NULL) || ((world->getObject(x,y+1) != NULL ) && ((world->getObject(x,y+1)->getType() == PIT) || (world->getObject(x,y+1)->getType() == GRASS)))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x,y+1) == NULL)
				{
					world->worldMap[x][y+1] = this;
					world->createObject(x, y, NULL);
					y++;
				}
				else if (world->getObject(x,y+1)->getType() == GRASS) //If moves on grass. Grass disappears and another re-appears somewhere else.
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
					y++;
				}
				else //If moves to a pit. Tiger falls.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		} 
		else if (direction == 2) //Moves tiger up if available.
		{
			if ((x > 0) && ((world->getObject(x-1,y) == NULL) || ((world->getObject(x-1,y) != NULL ) && ((world->getObject(x-1,y)->getType() == PIT) || (world->getObject(x-1,y)->getType() == GRASS)))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x-1,y) == NULL)
				{
					world->worldMap[x-1][y] = this;
					world->createObject(x, y, NULL);
					x--;
				}
				else if (world->getObject(x-1,y)->getType() == GRASS) //If moves on grass. Grass disappears and another re-appears somewhere else.
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
					x--;
				}
				else //If moves to a pit. Tiger falls.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		else if (direction == 3) //Moves tiger down if available.
		{
			if ((x < WORLDSIZE -1) && ((world->getObject(x+1,y) == NULL) || ((world->getObject(x+1,y) != NULL ) && ((world->getObject(x+1,y)->getType() == PIT) || (world->getObject(x+1,y)->getType() == GRASS)))))//Checks out of bounds and if space is available.
			{
				if (world->getObject(x+1,y) == NULL)
				{
					world->worldMap[x+1][y] = this;
					world->createObject(x, y, NULL);
					x++;
				}
				else if (world->getObject(x+1,y)->getType() == GRASS) //If moves on grass. Grass disappears and another re-appears somewhere else.
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
					x++;
				}
				else //If moves to a pit. Tiger falls.
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
void Tiger::breed()
{
	bool bred = false, leftSpace = true, rightSpace = true, upSpace = true, downSpace = true;
	while (bred == false)
	{	
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->worldMap[x][y-1] == NULL)) //Left space availability
			{
				Tiger *newTiger = new Tiger(world,x,y-1);
				world->createObject(x, y-1, newTiger);
				bred = true;
			}
			else
				leftSpace = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->worldMap[x][y+1] == NULL)) //Right space availability
			{
				Tiger *newTiger = new Tiger(world,x,y+1);
				world->createObject(x, y+1, newTiger);
				bred = true;
			}
			else rightSpace = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->worldMap[x-1][y] == NULL)) //Up space availability
			{
				Tiger *newTiger = new Tiger(world,x-1,y);
				world->createObject(x-1, y, newTiger);
				bred = true;
			}
			else upSpace = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 1) && (world->worldMap[x+1][y] == NULL)) //Down space availability
			{
				Tiger *newTiger = new Tiger(world,x+1,y);
				world->createObject(x+1, y, newTiger);
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
int Tiger::getType() const
{
	return 2;
}
int Tiger::numOfTigers = 0;
int Tiger::numBorn = 0;
int Tiger::numStarve = 0;
int Tiger::numCaptured = 0;
int Tiger::numFall = 0;
Tiger::~Tiger()
{
	numOfTigers--;
}
