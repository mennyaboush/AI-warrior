#include "Warrior.h"
#include "Action.h"
#include "Door.h"

Warrior::Warrior(Room &room, Point2D &location) :
	currentRoom(&room), location(location)
{
	// temp
	actionQueue.push(new Action(*this, Action::FIGHT, 10));
	actionQueue.push(new Action(*this, Action::FIND_AMMO, 0));
	actionQueue.push(new Action(*this, Action::RUN, 0));
	actionQueue.push(new Action(*this, Action::FIND_MED, 0));
}

Warrior::~Warrior()
{
}

/*Serch enemy in the maze
look in the current room, then go to another room and check him.*/
void Warrior::lookForEnemy(Warrior &other)
{
	//1. look for enemy in the current room.
	if (currentRoom->getId() != other.getCurrentRoom().getId())
		exitTheRoom(other.getCurrentRoom());
	else
		lookForEnemyInRoom(other);

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
	localAStar(other.getLocation());

	////Variables for A* algorithm
	//Node *current;

	//priority_queue<Node*, vector<Node*>, CompareNodes> pq;

	//vector<Point2D>::iterator gray_it;
	//vector<Point2D>::iterator black_it;
	//vector <Point2D> gray;
	//vector <Point2D> black;
	//vector <Parent> parents;
	//
	//bool finished = false;

	////A* action
	//pq.emplace(new Node(this->getLocation(), other.getLocation(), 0));
	//while (!finished)
	//{
	//	cout << "5" << endl;
	//	if (pq.empty())
	//	{
	//		cout << "pq should not be empty in this function!\n fnuctin:lookForEnemyInRoom ";
	//		return false; //Naver need to happend.
	//	}

	//	
	//	current = pq.top();
	//	pq.pop(); // remove it from pq
	//	parents.push_back(*new Parent(current->GetPoint(), current->GetPoint(), false));

	//	// the target has been found
	//	if (current->GetH() == 0)
	//	{
	//		finished = true;
	//	}
	//	// go back to start and enter the steps to walkingPath 
	//	vector<Parent>::iterator itr = find(parents.begin(), parents.end(),Parent(current->GetPoint(), current->GetPoint(), true));
	//	
	//	walkingPath.push(itr->GetCurrent());
	//	while (itr->HasParent())
	//	{
	//			Point2D tmp_prev = itr->GetPrev();
	//			Point2D tmp_cur = itr->GetCurrent();
	//			walkingPath.push(tmp_cur);
	//			itr = find(parents.begin(), parents.end(),
	//				Parent(tmp_prev, current->GetPoint(), true));
	//			cout << "3" << endl;

	//		}

	//	// check the neighbours
	//	
	//		// remove current from gray 
	//		gray_it = find(gray.begin(), gray.end(), current->GetPoint());
	//		if (gray_it != gray.end())
	//			gray.erase(gray_it);
	//		// and paint it black
	//		black.push_back(current->GetPoint());

	//		// try to go UP
	//		AddNode(*current, other.getLocation(), gray, black, parents, pq, ConstValue::UP);
	//		// try to go DOWN
	//		AddNode(*current, other.getLocation(), gray, black, parents, pq, ConstValue::DOWN);
	//		// try to go LEFT
	//		AddNode(*current, other.getLocation(), gray, black, parents, pq, ConstValue::LEFT);
	//		// try to go RIGHT
	//		AddNode(*current, other.getLocation(), gray, black, parents, pq, ConstValue::RIGHT);


	//		/*if (*(maze[current->GetPoint().GetY() + 1][current->GetPoint().GetX()]) == ConstValue::TARGET)
	//			finished = true;*/


	//} // while
	//return true;
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
	if (nextDoor == nullptr)
		cout << "null" << endl;
	//Point2D &p = doorDest->getEnterLocation();
	//this->localAStar(p);
	//3. got to the exit of the door.
	localAStar(nextDoor->getExitLocation());

	cout << "currentRoom: x: " << currentRoom->GetCenter().GetX() << " y: " << currentRoom->GetCenter().GetY() << endl;
	vector<Room*> v = nextDoor->getDestinations();
	currentRoom = v.front();
	cout << "currentRoom: x: " << currentRoom->GetCenter().GetX() << " y: " << currentRoom->GetCenter().GetY() << endl;

}

/*
this function assumed that the targetLocation in the same room,
and the targetLoction != location.
the function using a* algorithm to reach the targetLocation
*/
void Warrior::localAStar(Point2D &targetLocation)
{
	if (!currentRoom->locatedInTheRoom(targetLocation))
		cout << "localAStar need to switch room for reach " << targetLocation.GetX() << "," << targetLocation.GetY() << " cordinat.";

	//Variables for A* algorithm
	Node *current = nullptr;
	priority_queue<Node*, vector<Node*>, CompareNodes> pq; // the compare node claa may not considare the saftyScore.
	vector<Point2D>::iterator gray_it;
	vector<Point2D*>::iterator black_it;
	vector <Point2D> gray;
	vector <Point2D> black;
	vector <Parent> parents;
	bool finished = false;

	//A* action
	pq.emplace(new Node(this->getLocation(), targetLocation, 0));
	while (!finished)
	{
		if (pq.empty())
			cout << "pq should not be empty in this function!\n fnuctin:lookForEnemyInRoom ";
		cout << "1" << endl;

		vector<Parent>::iterator itr;

		//delete allocation
		if (current != nullptr)
			delete(current);

		current = pq.top();
		pq.pop(); // remove it from pq
		parents.push_back(*new Parent(current->GetPoint(), current->GetPoint(), false));

		// the target has been found
		if (current->GetH() == 0)
		{
			finished = true;

			// go back to start and enter the steps to walkingPath 
			itr = find(parents.begin(), parents.end(), Parent(current->GetPoint(), current->GetPoint(), true));
			walkingPath.push((itr->GetCurrent()));

			while (itr->HasParent())
			{
				Point2D &tmp_prev = itr->GetPrev();
				Point2D &tmp_cur = itr->GetCurrent();
				walkingPath.push(tmp_cur);
				itr = find(parents.begin(), parents.end(),
					Parent(tmp_prev, current->GetPoint(), true));
				cout << "6" << endl;

			}
		}

		// check the neighbours
		else
		{
			//remove current from gray 
			gray_it = find(gray.begin(), gray.end(), current->GetPoint());
			if (gray_it != gray.end())
				gray.erase(gray_it);

			// and paint it black
			black.push_back(current->GetPoint());

			// try to go UP
			AddNode(*current, targetLocation, gray, black, parents, pq, ConstValue::UP);
			// try to go DOWN
			AddNode(*current, targetLocation, gray, black, parents, pq, ConstValue::DOWN);
			// try to go LEFT
			AddNode(*current, targetLocation, gray, black, parents, pq, ConstValue::LEFT);
			// try to go RIGHT
			AddNode(*current, targetLocation, gray, black, parents, pq, ConstValue::RIGHT);

			//finished = addNeighborsAStarHelper(*current, targetLocation, gray, parents, pq);
		}
	} // while
}
/*
Each close wall in the area increases the score by 1.
The function tests a 3X3 area when the warrior is in the center of the area.
*/
void Warrior::refrashSafetyScore()
{
	int score = 0, i, j;
	int x = this->location.GetX();
	int y = this->location.GetY();
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{

		}
	}
}

/*
Each shot consumes one ball.
The damage caused to the second fighter depends on the distance between them
*/
void Warrior::shoot(Warrior &other)
{
	//Check the ammo.
	if (this->gunsAmmo > 0)
	{
		double distance = getDistance(other);

		//check if the warrior no too far
		int damage = ConstValue::MAX_DISTANCE_TO_INJURED - (int)distance;
		if (damage > 0)
		{
			gunsAmmo--;
			std::cout << this->id << " shot " << other.id;
			other.injured(damage);
		}
		else
			localAStar(other.getCurrentRoom().GetCenter());
	}
}

/*this function help to A* and do 2 things
1. create new node who represent the step for UP direction and push him to priortyQ and to gray vector.
2. creat parant and push him to the parant collaction.
*/
void Warrior::addNodeAStarHelper(Node & currentNode, Node & nextNode, Point2D & targetLocation, vector<Point2D>& gray, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq)
{
	//1. create new node from current to target
	gray.push_back(nextNode.GetPoint());
	pq.emplace(&nextNode);

	//2. creat parant and push him to the parant collaction.
	Parent *p = new Parent(nextNode.GetPoint(), currentNode.GetPoint(), true);
	parents.push_back(*p);
}

bool Warrior::AddNode(Node & current, Point2D & targetLocation, vector<Point2D>& gray, vector<Point2D>& black, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq, int direction)
{
	Node* tmp;
	Point2D* pt;
	vector<Point2D>::iterator gray_it;
	vector<Point2D>::iterator black_it;
	double space_weight = 0.1, wall_weight = 5, weight;
	int dx, dy;
	bool finished = false;

	switch (direction)
	{
	case ConstValue::UP:
		dx = 0;
		dy = -1;
		break;
	case ConstValue::DOWN:
		dx = 0;
		dy = 1;
		break;
	case ConstValue::LEFT:
		dx = -1;
		dy = 0;
		break;
	case ConstValue::RIGHT:
		dx = 1;
		dy = 0;
		break;
	} // switch

	if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() - 1].getType() == ConstValue::TARGET)
		finished = true;

	if (direction == ConstValue::UP && current.GetPoint().GetY() > 0 ||
		direction == ConstValue::DOWN && current.GetPoint().GetY() < ConstValue::MSIZE - 1 ||
		direction == ConstValue::LEFT && current.GetPoint().GetX() > 0 ||
		direction == ConstValue::RIGHT && current.GetPoint().GetX() < ConstValue::MSIZE - 1)
	{
		pt = new Point2D(current.GetPoint().GetX() + dx, current.GetPoint().GetY() + dy);
		gray_it = find(gray.begin(), gray.end(), *pt);
		black_it = find(black.begin(), black.end(), *pt);
		if (gray_it == gray.end() && black_it == black.end()) // this is a new point
		{
			// very important to tunnels
			if (maze->parts[current.GetPoint().GetY() + dy][current.GetPoint().GetX() + dx].getType() == ConstValue::WALL)
				weight = wall_weight;
			else weight = space_weight;
			// weight depends on previous weight and wheater we had to dig
			// to this point or not
			tmp = new Node(*pt, targetLocation, current.GetG() + weight);
			pq.emplace(tmp); // insert first node to priority queue
			gray.push_back(*pt); // paint it gray
			// add Parent
			parents.push_back(Parent(tmp->GetPoint(), current.GetPoint(), true));
		}
	}
	return finished;
}

/*get a node and enter all the neighbors to the gray,parents and pq */
bool Warrior::addNeighborsAStarHelper(Node & current, Point2D & targetLocation, vector<Point2D>& gray, vector<Parent>& parents, priority_queue<Node*, vector<Node*>, CompareNodes>& pq)
{
	bool finished = false;

	// try to go UP
	if (maze->parts[current.GetPoint().GetY() + 1][current.GetPoint().GetX()].getType() == ConstValue::TARGET)
		finished = true;
	else if (maze->parts[current.GetPoint().GetY() + 1][current.GetPoint().GetX()].getType() != ConstValue::WALL)
	{
		//1. create new node who represent the step for UP direction and push him to priortyQ and to gray vector.
		Node *up = new Node(Point2D(current.GetPoint().GetX(), current.GetPoint().GetY() + 1), targetLocation, 0);
		addNodeAStarHelper(current, *up, targetLocation, gray, parents, pq);
	}

	// try to go DOWN
	if (maze->parts[current.GetPoint().GetY() - 1][current.GetPoint().GetX()].getType() == ConstValue::TARGET)
		finished = true;
	else if (maze->parts[current.GetPoint().GetY() - 1][current.GetPoint().GetX()].getType() != ConstValue::WALL)
	{
		Node *down = new Node(Point2D(current.GetPoint().GetX(), current.GetPoint().GetY() - 1), targetLocation, 0);
		addNodeAStarHelper(current, *down, targetLocation, gray, parents, pq);
	}

	// try to go LAFT
	if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() - 1].getType() == ConstValue::TARGET)
		finished = true;
	else if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() - 1].getType() != ConstValue::WALL)
	{
		Node *left = new Node(Point2D(current.GetPoint().GetX() - 1, current.GetPoint().GetY()), targetLocation, 0);
		addNodeAStarHelper(current, *left, targetLocation, gray, parents, pq);
	}

	// try to go RIGHT
	if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() + 1].getType() == ConstValue::TARGET)
		finished = true;
	else if (maze->parts[current.GetPoint().GetY()][current.GetPoint().GetX() + 1].getType() != ConstValue::WALL)
	{
		Node *right = new Node(Point2D(current.GetPoint().GetX() + 1, current.GetPoint().GetY()), targetLocation, 0);
		addNodeAStarHelper(current, *right, targetLocation, gray, parents, pq);
	}
	return finished;
}


/*Get a point and move the warrior on the maze to the point cordinate*/
void Warrior::moveWarrior(Point2D & nextStep)
{
	//deleate the warrior from the maze
	maze->parts[location.GetY()][location.GetX()].setType(ConstValue::SPACE);

	//change the location of warrior.
	this->location.setX(nextStep.GetX());
	this->location.setY(nextStep.GetY());

	//draw the warrior on the maze
	maze->parts[location.GetY()][location.GetX()].setType(ConstValue::WARRIOR);
}

/* Decrease the life point until dead. */
void Warrior::injured(int hitPoint)
{
	//id = generatorId++;
	lifePoint = lifePoint - hitPoint;
	if (lifePoint <= 0)
	{
		lifePoint = 0;
		life = false;
	}
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
		//Action toDo = *(actionQueue.top());	// RUN, FIND_AMMO, FIND_MED, FIGHT
	//actionQueue.pop();

		lookForEnemy(other);
		//switch (toDo.getType())
		//{
		//case Action::FIGHT:
		//	lookForEnemy(other);
		//	// do 20 steps in the derection of the other warrior and fight if close enought
		//	break;
		//case Action::RUN:
		//	// do 20 steps in opposite derections of the other warrior
		//	//runAway();
		//	break;
		//case Action::FIND_AMMO:
		//	// go through rooms and look for ammo
		//	break;
		//case Action::FIND_MED:
		//	// go through rooms and look for med
		//	break;
		//}
	}

}

