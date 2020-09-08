//Main program for project 5.
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "common.h"
#include "rabbit.h"
#include "tiger.h"
#include "hunter.h"
#include "grass.h"
#include "pit.h"
using std::cout;
using namespace std;
int main()
{
	World theWorld; //Creates world.
	int numOfRabbits, numOfTigers, numOfHunters, numOfGrasses, numOfPits, numOfSteps = 0; //Initializes number of steps and creates variables for user input.
	//Asks user to enter desired numbers.
	cout << "Enter initial number of rabbits: ";
	cin >> numOfRabbits;
	cout << "Enter initial number of tigers: ";
	cin >> numOfTigers;
	cout << "Enter initial number of hunters: ";
	cin >> numOfHunters;
	cout << "Enter initial number of grasses: ";
	cin >> numOfGrasses;
	cout << "Enter initial number of pits: ";
	cin >> numOfPits;
	srand(time(0)); //For randomness.
	if (numOfRabbits + numOfTigers + numOfHunters + numOfGrasses + numOfPits > WORLDSIZE*WORLDSIZE)
	{
		cout <<"Exceed maximum number of objects allowed to be created. Terminating program." << endl;
		exit(1);
	}
	for (int index = 0; index < numOfRabbits + numOfTigers + numOfHunters + numOfGrasses + numOfPits; index++)
	{
		bool objectCreated = false;
		while (objectCreated == false)
		{
			int x = (rand()%WORLDSIZE);
			int y = (rand()%WORLDSIZE);
			if (theWorld.getObject(x, y) == NULL)
			{
				if (index < numOfPits)
				{
					Pit *newPit = new Pit(&theWorld,x,y);
					theWorld.createObject(x, y, newPit);
				}
				else if (index < numOfPits + numOfGrasses)
				{
					Grass *newGrass = new Grass(&theWorld,x,y);
					theWorld.createObject(x, y, newGrass);
				}
				else if (index < numOfPits + numOfGrasses + numOfHunters)
				{
					Hunter *newHunter = new Hunter(&theWorld,x,y);
					theWorld.createObject(x, y, newHunter);
				}
				else if (index < numOfPits + numOfGrasses + numOfHunters + numOfTigers)
				{
					Tiger *newTiger = new Tiger(&theWorld,x,y);
					theWorld.createObject(x, y, newTiger);
				}
				else
				{
					Rabbit *newRabbit = new Rabbit(&theWorld,x,y);
					theWorld.createObject(x, y, newRabbit);
				}
				objectCreated = true;
			}
		}
	}
	//Initial map is displayed.
	getchar();
	system("clear");
	cout << "Time_step: " << numOfSteps << "\n\n";
	theWorld.printStep();
	//Loops until no hunters, tigers, nor rabbits are alive.
	while (Hunter::numOfHunters + Tiger::numOfTigers + Rabbit::numOfRabbits != 0)
	{
		theWorld.resetVariables();
		cout << "\nPress Enter to proceed\n";
		numOfSteps++;
		theWorld.nextStep();
		getchar();
		system("clear");
		cout <<"Time_step: " <<numOfSteps << "\n\n";
		theWorld.printStep();
	}
	//Terminates program when all animals die.
	cout << "All animals have died. Program has ended." << endl;
}
