#pragma once
#include "Point2D.h"
#include "Room.h"
#include <iostream>
#include <math.h>
#include <queue>
#include "Node.h"
#include "CompareNodes.h"

/*
The warrior need to implements 2 praiorty Q 
to select a mission 
and for nevigation.
*/
using namespace std;
static int generatorId = 0;

class Warrior
{

private:
	int id;
	Room *currentRoom;
	Point2D location;
	int lifePoint = 100; //range [0,100]
	int gunsAmmo = 50; // 50 bullets
	int grenadeAmmo = 2; // 2 grenades
	int safetyScore; // Depends on walls neer the warrior 
	int *maze[ConstValue::MSIZE][ConstValue::MSIZE];
	bool life = true;

	//functions
	void lookForMedicalStorageInTheRoom();
	void lookForAmmoStorageInTheRoom();
	void refrashSafetyScore(); //scan the area and change the safetyScore.
	void exitTheRoom(); //Implaments in A*.
	void shoot(Warrior &other);
	void getClose(Point2D targetLoction);
	void injured(int hitPoint);
	void throGrenade();
	int getDistance(const Warrior &other) const;
	bool lookForEnemyInRoom(Warrior &other);

public:
	void lookForEnemy(Warrior &other);
	void lookForMedicalStorage();
	void lookForAmmoStorage();
	void runAway();// maybe it can use in lookForMedical?
	void fight();
	Point2D getLocation() const { return this->location; }
	void setX(int x) { this->location.setX(x); }
	void setY(int y) { this->location.setY(y); }
	bool isALife() const { return life; }
	Warrior();
	Warrior(int maze[ConstValue::MSIZE][ConstValue::MSIZE], Room room);
	~Warrior();
};

