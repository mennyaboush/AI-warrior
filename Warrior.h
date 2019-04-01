#pragma once

#include "Point2D.h"
#include "Room.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include "CompareNodes.h"
#include "CompareActions.h"
#include "ConstValue.h"
#include "Parent.h"
#include "Action.h"
#include "Maze.h"

class Maze;
using namespace std;

/*
The warrior need to implements 2 praiorty Q
to select a mission
and for nevigation.
*/
class Warrior
{
private:
	//const values.
	const int MAX_LIFE = 100;
	const int MAX_GUNS_AMMO = 50;
	const int MAX_GRANDE_AMMO = 2;

	//variables.
	Maze* maze;

	int		id;
	int		lifePoint = MAX_LIFE; //range [0,100]
	int		gunsAmmo = MAX_GUNS_AMMO;
	int		grenadeAmmo = MAX_GRANDE_AMMO; 
	int		safetyScore; // Depends on walls neer the warrior 

	bool	life = true;

	Room	*currentRoom;
	Point2D	location;

	stack<Point2D> walkingPath;
	priority_queue<Action*, vector<Action*>, CompareActions> actionQueue;

	Action *currentAction;

	//functions
	void exitTheRoom(Room &room); //Implaments in A*.
	double getDistance(const Warrior &other) const;
	void lookForEnemyInRoom(Warrior &other);
	
//	void lookForMedicalStorageInTheRoom();
	//void lookForAmmoStorageInTheRoom();
	//void refrashSafetyScore(); //scan the area and change the safetyScore.
	void shoot(Warrior &other);
	void injured(int hitPoint);
	//void throGrenade();
	//void addNodeAStarHelper(Node &currentNode, Node &nextNode, Point2D &targetLocation, vector <Point2D> &gray, vector <Parent> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	//void addNodeAStarHelper(Node &currentNode, Node &nextNode, Point2D &targetLocation, vector <Point2D*> &gray, vector <Parent*> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	//bool addNeighborsAStarHelper(Node &current, Point2D &targetLocation, vector <Point2D> &gray, vector <Parent> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	//bool addNeighborsAStarHelper(Node &current, Point2D &targetLocation, vector <Point2D*> &gray, vector <Parent*> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);

public:
	Warrior(Room &room, Point2D &location);
	~Warrior();

	void selectMission(Warrior& other);
	void moveWarrior(Point2D &nextStep);

	void lookForEnemy(Warrior &other);
	void lookForMedicalStorage();

	//getters & setters
	int getlifePoints() { return lifePoint; }
	int	getGunsAmmo() { return gunsAmmo; }
	int	getGrenadeAmmo() { return grenadeAmmo; }
	Room& getCurrentRoom() { return *currentRoom; }
	Point2D getLocation() const { return location; }
	double getMaxLife() const { return MAX_LIFE; }
	double getMaxGuns() const { return MAX_GUNS_AMMO; }
	double getMaxGrandes() const { return MAX_GRANDE_AMMO; }

	void setX(int x) { this->location.setX(x); }
	void setY(int y) { this->location.setY(y); }
	bool isAlive() const { return life; }

};

