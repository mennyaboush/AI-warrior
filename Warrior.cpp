#include "Warrior.h"
#include "Action.h"
#include "Door.h"
#include "CompareActions.h"

/**
ToDo:
- search for ammo&med
- run away
- shoot
*/


Warrior::Warrior(Room &room, Point2D &location) :
	currentRoom(&room), location(location)
{
	maze = &Maze::getInstance();
	static int genId = 0;
	this->id = genId++;
	actionQueue.push(new Action(*this, Action::FIGHT));
	actionQueue.push(new Action(*this, Action::FIND_AMMO));
	actionQueue.push(new Action(*this, Action::RUN));
	actionQueue.push(new Action(*this, Action::FIND_MED));
}

Warrior::~Warrior()
{
	// delete actionQueue
	// ..
}

/*go to the next room to reach the destination room */
void Warrior::exitTheRoom(Room &destRoom)
{
	//1. serch the door with the destionation.
	vector<Door*> doors = currentRoom->getDoors();
	int numOfDoors = doors.size();
	Door *nextDoor = nullptr;
	for (int i = 0; i < numOfDoors; i++)
	{
		if (doors[i]->isDestinationDoor(destRoom))
		{
			nextDoor = doors[i];
			break;
		}
	}

	//2. go to the enter of door.
	//Point2D &p = doorDest->getEnterLocation();
	//this->localAStar(p);
	//3. got to the exit of the door.

	walkingPath = maze->localAStar(location, nextDoor->getExitLocation());

	cout << "currentRoom: x: " << currentRoom->GetCenter().GetX() << " y: " << currentRoom->GetCenter().GetY() << endl;
	vector<Room*> v = nextDoor->getDestinations();
	currentRoom = v.front();
	cout << "currentRoom: x: " << currentRoom->GetCenter().GetX() << " y: " << currentRoom->GetCenter().GetY() << endl;
}

double Warrior::getDistance(const Warrior & other) const
{
	int x = this->location.GetX() - other.location.GetX();
	int y = this->location.GetY() - other.location.GetY();

	return sqrt(pow(x, 2) + pow(y, 2));
}

/*Warrior select a mission.
if the warrior started to walk he keep going
else he select new mission.*/
void Warrior::selectMission(Warrior& other)
{
	if (walkingPath.size() > 0)
	{
		moveWarrior(walkingPath.top());
		walkingPath.pop();
	}
	else
	{
		current = actionQueue.top();	// RUN, FIND_AMMO, FIND_MED, FIGHT
		//actionQueue.pop();

		lookForEnemy(other);
		//switch (current->getType())
		//{
		//case Action::FIGHT:
		//	lookForEnemy(other);
		//	break;
		//case Action::RUN:
		//	// runAway();
		//	break;
		//case Action::FIND_AMMO:
		//	// target of Astar is ammo
		//	break;
		//case Action::FIND_MED:
		//	// target of Astar is med
		//	break;
		//}
	}
}

/*Serch enemy in the maze
look in the current room, then go to another room and check him.*/
void Warrior::lookForEnemy(Warrior &other)
{
	//1. look for enemy in the current room.
	if (currentRoom->getId() != other.getCurrentRoom().getId()) 
		exitTheRoom(other.getCurrentRoom());
	else
		lookForEnemyInRoom(other); // enemy is in the room

	//2. calculat the next room the warrior will check.

	//3. go to next room  safely as possible.

	//4. look for enemy in the current room.
}

/*
Look for other warrior in room using A* algorithm
use stack::walkingPath to save the steps and move the warrior.
*/
void Warrior::lookForEnemyInRoom(Warrior &other)
{
	if (getDistance(other) < ConstValue::SHOOT_MAX_DISTANCE)
		shoot(other);
	else
		walkingPath = maze->localAStar(location, other.getLocation());
}

/*The medical storage in the same room.
the warrior use a* algorithm to reach the storage and get healed*/
void Warrior::lookForMedicalStorage()
{
	maze->goToTheClosestMedicalStorage(*this);
}

/*Get a point and move the warrior on the maze to the point cordinate*/
void Warrior::moveWarrior(Point2D & nextStep)
{
	//deleate the warrior from the maze
	maze->parts[location.GetY()][location.GetX()].setType(MazePart::SPACE);

	//change the location of warrior.
	this->location.setX(nextStep.GetX());
	this->location.setY(nextStep.GetY());

	//draw the warrior on the maze
	maze->parts[location.GetY()][location.GetX()].setType(MazePart::WARRIOR);
}


/*
Each shot consumes one ball.
The damage caused to the second fighter depends on the distance between them
*/
void Warrior::shoot(Warrior &other)
{
	if (gunsAmmo <= 0)
		return;
	//Check the ammo.
	double distance = getDistance(other);

	cout << "warrior " << id << " is trying to soot" << endl;
	//check if the warrior no too far
	int damage = ConstValue::SHOOT_MAX_DISTANCE - (int)distance;
	if (damage > 0)
	{
		current->updateScore(-2);
		gunsAmmo--;
		cout << this->id << " shot! " << other.id << endl;
		other.injured(damage);
	}
	else
		walkingPath = maze->localAStar(location, other.getCurrentRoom().GetCenter());
}

/* Decrease the life point until dead. */
void Warrior::injured(int hitPoint)
{
	// TODO: update action med and action run priority
	
	lifePoint = lifePoint - hitPoint;
	if (lifePoint <= 0)
	{
		lifePoint = 0;
		life = false;
	}
}

///*
//Each close wall in the area increases the score by 1.
//The function tests a 3X3 area when the warrior is in the center of the area.
//*/
//void Warrior::refrashSafetyScore()
//{
//	int score = 0, i, j;
//	int x = this->location.GetX();
//	int y = this->location.GetY();
//	for (i = x - 1; i <= x + 1; i++)
//	{
//		for (j = y - 1; j <= y + 1; j++)
//		{
//
//		}
//	}
//}



///*this function help to A* and do 2 things
//1. create new node who represent the step for UP direction and push him to priortyQ and to gray vector.
//2. creat parant and push him to the parant collaction.
//*/
//void Warrior::addNodeAStarHelper(Node & currentNode, Node & nextNode, Point2D & targetLocation, vector<Point2D>& gray, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq)
//{
//	//1. create new node from current to target
//	gray.push_back(nextNode.GetPoint());
//	pq.emplace(&nextNode);
//
//	//2. creat parant and push him to the parant collaction.
//	Parent *p = new Parent(nextNode.GetPoint(), currentNode.GetPoint(), true);
//	parents.push_back(*p);
//}

///*get a node and enter all the neighbors to the gray,parents and pq */
//bool Warrior::addNeighborsAStarHelper(Node & current, Point2D & targetLocation, vector<Point2D>& gray, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq)
//{
//	bool finished = false;
//
//	// try to go UP
//	if (maze->parts[current.GetPoint().GetY() + 1][current.GetPoint().GetX()].getType() == ConstValue::TARGET)
//		finished = true;
//	else if (maze->parts[current.GetPoint().GetY() + 1][current.GetPoint().GetX()].getType() != ConstValue::WALL)
//	{
//		//1. create new node who represent the step for UP direction and push him to priortyQ and to gray vector.
//		Node *up = new Node(Point2D(current.GetPoint().GetX(), current.GetPoint().GetY() + 1), targetLocation, 0);
//		addNodeAStarHelper(current, *up, targetLocation, gray, parents, pq);
//	}
//
//	// try to go DOWN
//	if (maze->parts[current.GetPoint().GetY() - 1][current.GetPoint().GetX()].getType() == ConstValue::TARGET)
//		finished = true;
//	else if (maze->parts[current.GetPoint().GetY() - 1][current.GetPoint().GetX()].getType() != ConstValue::WALL)
//	{
//		Node *down = new Node(Point2D(current.GetPoint().GetX(), current.GetPoint().GetY() - 1), targetLocation, 0);
//		addNodeAStarHelper(current, *down, targetLocation, gray, parents, pq);
//	}
//
//	// try to go LAFT
//	if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() - 1].getType() == ConstValue::TARGET)
//		finished = true;
//	else if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() - 1].getType() != ConstValue::WALL)
//	{
//		Node *left = new Node(Point2D(current.GetPoint().GetX() - 1, current.GetPoint().GetY()), targetLocation, 0);
//		addNodeAStarHelper(current, *left, targetLocation, gray, parents, pq);
//	}
//
//	// try to go RIGHT
//	if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() + 1].getType() == ConstValue::TARGET)
//		finished = true;
//	else if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() + 1].getType() != ConstValue::WALL)
//	{
//		Node *right = new Node(Point2D(current.GetPoint().GetX() + 1, current.GetPoint().GetY()), targetLocation, 0);
//		addNodeAStarHelper(current, *right, targetLocation, gray, parents, pq);
//	}
//	return finished;
//}


