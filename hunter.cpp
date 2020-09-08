//This is the file hunter.cpp.
//This is the implementation for the class Hunter.
//The interface for the class Hunter is in
//the header file hunter.h.
#include <iostream>
#include <cstdlib>
#include <ctime> //For rand.
#include "hunter.h"
#include "tiger.h"
#include "rabbit.h"
#include "grass.h"
#include <iostream>
using std::cout;
Hunter::Hunter() : Common()
{
	numBorn++;
	numOfHunters++;
}
Hunter::Hunter(World *worldPtr, int X, int Y) : Common(worldPtr,X,Y)
{
	numBorn++;
	numOfHunters++;
}
void Hunter::move()
{//Searches hunter's surrounding area for a tiger or rabbit. The hunter will hunt the closest random available tiger or rabbit, or move to an adjacent empty space if there are no available tigers or rabbits, or stay in the same position if there are no available spaces to move.
	bool adjacentCritterAvailable = true, rangedCritterAvailable = true, leftCritter1 = true, leftCritter2 = true, rightCritter1 = true, rightCritter2 = true, upCritter1 = true, upCritter2 = true, downCritter1 = true, downCritter2 = true;
	while ((movement == false) && (adjacentCritterAvailable == true))
	{
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->getObject(x, y-1) != NULL) && ((world->getObject(x, y-1)->getType() == TIGER) || (world->getObject(x, y-1)->getType() == RABBIT))) //Adjacent left critter availability
			{
				if (world->getObject(x, y-1)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x][y-1]);
				world->worldMap[x][y-1] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				y--;
			}
			else
				leftCritter1 = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->getObject(x, y+1) != NULL) && ((world->getObject(x, y+1)->getType() == TIGER) || (world->getObject(x, y+1)->getType() == RABBIT))) //Adjacent right critter availability
			{
				if (world->getObject(x, y+1)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				stamina = STARVE; //Resets starve countdown.
				delete (world->worldMap[x][y+1]);
				world->worldMap[x][y+1] = this;
				world->createObject(x, y, NULL);
				movement = true;
				lifetime++;
				y++;
			}
			else rightCritter1 = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->getObject(x-1, y) != NULL) && ((world->getObject(x-1,y)->getType() == TIGER) || (world->getObject(x-1,y)->getType() == RABBIT))) //Adjacent up critter availability
			{
				if (world->getObject(x-1, y)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				stamina = STARVE; //Resets starve countdown.
				delete (world->worldMap[x-1][y]);
				world->worldMap[x-1][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				lifetime++;
				x--;
			}
			else upCritter1 = false;
		}
		else if (direction == STARVE)
		{
			if ((x < WORLDSIZE - 1) && (world->getObject(x+1, y) != NULL) && ((world->getObject(x+1,y)->getType() == TIGER) ||(world->getObject(x+1,y)->getType() == RABBIT))) //Adjacent down critter availability
			{
				if (world->getObject(x+1, y)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x+1][y]);
				world->worldMap[x+1][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				x++;
			}
			else downCritter1 = false;
		}
		if ((leftCritter1 == false) && (rightCritter1 == false) && (upCritter1 == false) && (downCritter1 == false))
			adjacentCritterAvailable = false;
	}
	while ((movement == false) && (rangedCritterAvailable == true))
	{
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 1) && (world->getObject(x, y-2) != NULL) && ((world->getObject(x, y-2)->getType() == TIGER) || (world->getObject(x, y-2)->getType() == RABBIT))) //Ranged left critter availability
			{
				if (world->getObject(x, y-2)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x][y-2]);
				world->worldMap[x][y-2] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				y -= 2;
			}
			else
				leftCritter2 = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 2) && (world->getObject(x, y+2) != NULL) && ((world->getObject(x, y+2)->getType() == TIGER) || (world->getObject(x, y+2)->getType() == RABBIT))) //Ranged right critter availability
			{
				if (world->getObject(x, y+2)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x][y+2]);
				world->worldMap[x][y+2] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				y += 2;
			}
			else rightCritter2 = false;
		}
		else if (direction == 2)
		{
			if ((x > 1) && (world->getObject(x-2, y) != NULL) && ((world->getObject(x-2,y)->getType() == TIGER) || (world->getObject(x-2,y)->getType() == RABBIT))) //Ranged up critter availability
			{
				if (world->getObject(x-2, y)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x-2][y]);
				world->worldMap[x-2][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				x -= 2;
			}
			else upCritter2 = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 2) && (world->getObject(x+2, y) != NULL) && ((world->getObject(x+2,y)->getType() == TIGER) ||(world->getObject(x+2,y)->getType() == RABBIT))) //Ranged down critter availability
			{
				if (world->getObject(x+2, y)->getType() == TIGER)
					Tiger::numCaptured++;
				else
					Rabbit::numCaptured++;
				delete (world->worldMap[x+2][y]);
				world->worldMap[x+2][y] = this;
				world->createObject(x, y, NULL);
				movement = true;
				stamina = STARVE;
				lifetime++;
				x += 2;
			}
			else downCritter2 = false;
		}
		if ((leftCritter2 == false) && (rightCritter2 == false) && (upCritter2 == false) && (downCritter2 == false))
			rangedCritterAvailable = false;
	}
	if (movement == false) //Hunter moves to an empty space or pit or steps on a grass if it did not eat a critter or stays in same location if the space is taken or off the grid.
	{
		int direction (rand()%4);
		if (direction == 0) //Moves hunter left if available.
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
				else //If moves to a pit. Hunter falls.
				{
					delete (world->worldMap[x][y]);
					world->createObject(x, y, NULL);
					numFall++;
				}
				movement = true;
			}
		}
		else if (direction == 1) //Moves hunter right if available.
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
		else if (direction == 2) //Moves hunter up if available.
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
		else if (direction == 3) //Moves hunter down if available.
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
void Hunter::breed()
{
	bool bred = false, leftSpace = true, rightSpace = true, upSpace = true, downSpace = true;
	while (bred == false)
	{
		
		int direction = (rand()%4);
		if (direction == 0)
		{
			if ((y > 0) && (world->worldMap[x][y-1] == NULL)) //Left space availability
			{
				Hunter *newHunter = new Hunter(world,x,y-1);
				world->createObject(x, y-1, newHunter);
				bred = true;
			}
			else
				leftSpace = false;
		}
		else if (direction == 1)
		{
			if ((y < WORLDSIZE - 1) && (world->worldMap[x][y+1] == NULL)) //Right space availability
			{
				Hunter *newHunter = new Hunter(world,x,y+1);
				world->createObject(x, y+1, newHunter);
				bred = true;
			}
			else rightSpace = false;
		}
		else if (direction == 2)
		{
			if ((x > 0) && (world->worldMap[x-1][y] == NULL)) //Up space availability
			{
				Hunter *newHunter = new Hunter(world,x-1,y);
				world->createObject(x-1, y, newHunter);
				bred = true;
			}
			else upSpace = false;
		}
		else if (direction == 3)
		{
			if ((x < WORLDSIZE - 1) && (world->worldMap[x+1][y] == NULL)) //Down space availability
			{
				Hunter *newHunter = new Hunter(world,x+1,y);
				world->createObject(x+1, y, newHunter);
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
int Hunter::getType() const
{
	return 3;
}
int Hunter::numOfHunters = 0;
int Hunter::numBorn = 0;
int Hunter::numStarve = 0;
int Hunter::numCaptured = 0;
int Hunter::numFall = 0;
Hunter::~Hunter()
{
	numOfHunters--;
}
