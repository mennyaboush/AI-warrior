#pragma once
#include "Point2D.h"
#include "Room.h"
/*
The warrior need to implements 2 praiorty Q 
to select a mission 
and for nevigation.
*/
class Warrior
{
private:
	int id;
	Point2D location;
	int lifePoint = 100; //range [0,100]
	int gunsAmmo = 50; // 50 bullets
	int grenadeAmmo = 2; // 2 grenades
	int safetyScore; // Depends on walls neer the warrior 
	int *maze[ConstValue::MSIZE][ConstValue::MSIZE];
	
	//functions
	void lookForMedicalStorageInTheRoom();
	void lookForAmmoStorageInTheRoom();
	void refrashSafetyScore(); //scan the area and change the safetyScore.
	void exitTheRoom(); //Implaments in A*.
public:
	void lookForMedicalStorage();
	void lookForAmmoStorage();
	void runAway();// maybe it can use in lookForMedical?
	Warrior();
	Warrior(int maze[ConstValue::MSIZE][ConstValue::MSIZE], Room room);
	~Warrior();
};

