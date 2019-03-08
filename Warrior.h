#pragma once

#include "Point2D.h"
#include "Room.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <iostream>
#include "CompareNodes.h"
#include "CompareActions.h"

class Action;
using namespace std;

/*
The warrior need to implements 2 praiorty Q 
to select a mission 
and for nevigation.
*/
class Warrior
{
private:
	
	int		id;
	int		lifePoint = 100; //range [0,100]
	int		gunsAmmo = 50; // 50 bullets
	int		grenadeAmmo = 2; // 2 grenades
	int		safetyScore; // Depends on walls neer the warrior 
	int		***maze;

	Point2D	location;
	
	priority_queue<Action, vector<Action>, CompareActions> actionQueue;

	//functions
	void lookForMedicalStorageInTheRoom();
	void lookForAmmoStorageInTheRoom();
	void refrashSafetyScore(); //scan the area and change the safetyScore.
	void exitTheRoom(); //Implaments in A*.
public:
	Warrior(int ***maze, Room room);
	~Warrior();
	//void lookForMedicalStorage();
	//void lookForAmmoStorage();
	//void runAway();// maybe it can use in lookForMedical?
	//
	void lookForTarget(Point2D target);
	void moveWarrior();
	

	//getters
	int getlifePoints() { return lifePoint; }
	int	getGunsAmmo() { return gunsAmmo; }
	int	getGrenadeAmmo() { return grenadeAmmo; }
};

