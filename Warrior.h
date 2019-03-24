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
#include "Maze.h"

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
	bool	life = true;
	
	Maze maze = Maze::getInstance();
	Room	*currentRoom;
	Point2D	location;
	
	stack<Point2D> walkingPath;
	priority_queue<Action*, vector<Action*>, CompareActions> actionQueue;

	//functions
	void lookForMedicalStorageInTheRoom();
	void lookForAmmoStorageInTheRoom();
	void refrashSafetyScore(); //scan the area and change the safetyScore.
	void exitTheRoom(Room &room); //Implaments in A*.
	void shoot(Warrior &other);
	void localAStar(Point2D &targetLoction);
	void injured(int hitPoint);
	void throGrenade();
	double getDistance(const Warrior &other) const;
	void lookForEnemyInRoom(Warrior &other);
	bool AddNode(Node & current, Point2D & targetLocation, vector<Point2D>& gray, vector<Point2D>& black, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq, int direction);
	
	void addNodeAStarHelper(Node &currentNode, Node &nextNode, Point2D &targetLocation, vector <Point2D> &gray, vector <Parent> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	//void addNodeAStarHelper(Node &currentNode, Node &nextNode, Point2D &targetLocation, vector <Point2D*> &gray, vector <Parent*> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	bool addNeighborsAStarHelper(Node &current, Point2D &targetLocation, vector <Point2D> &gray, vector <Parent> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);
	//bool addNeighborsAStarHelper(Node &current, Point2D &targetLocation, vector <Point2D*> &gray, vector <Parent*> &parents, priority_queue<Node*, vector<Node*>, CompareNodes> &pq);

public:
	Warrior(Room &room, Point2D &location);
	~Warrior();

	void selectMission(Warrior& other);
	void moveWarrior(Point2D &nextStep);

	void lookForEnemy(Warrior &other);

	//getters & setters
	int getlifePoints() { return lifePoint; }
	int	getGunsAmmo() { return gunsAmmo; }
	int	getGrenadeAmmo() { return grenadeAmmo; }
	Room& getCurrentRoom() { return *currentRoom; }
	Point2D getLocation() const 
	{
		return location; 
	}
	void setX(int x) { this->location.setX(x); }
	void setY(int y) { this->location.setY(y); }
	bool isALife() const { return life; }

};

