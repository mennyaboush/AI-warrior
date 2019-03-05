#include "Warrior.h"
#include "Parent.h"

Warrior::Warrior()
{
}

Warrior::Warrior(int maze[ConstValue::MSIZE][ConstValue::MSIZE] ,Room room)
{
	//Save referance to maze.
	int i;
	for (i = 0; i < ConstValue::MSIZE; i++) {
		*(this->maze)[i] = maze[i];
	}
	this->location = room.GetCenter();
	this->currentRoom = &room;
	//refrashSafetyScore();
}


Warrior::~Warrior()
{
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
//			if(this->)
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
		int distance = getDistance(other);
		
		//check if the warrior no too far
		int damage = ConstValue::MAX_DISTANCE_TO_INJURED - distance;
		if (damage > 0)
		{
			gunsAmmo--;
			std::cout << this->id << " shot " << other.id;
			other.injured(damage);
		}
		else
			getClose(other.location);
	}
}

/*
this function assumed that the targetLocation in the same room,
and the targetLoction != location.
*/
void Warrior::getClose(Point2D targetLoction)
{
	if (targetLoction.GetX() > location.GetX())
		location.setX(location.GetX() + 1);
	else if(targetLoction.GetX() < location.GetX())
		location.setX(location.GetX() - 1);
	else if(targetLoction.GetY() > location.GetY())
		location.setY(location.GetY() + 1);
	else 
		location.setY(location.GetY() - 1);
}

/* Decrease the life point until dead. */
void Warrior::injured(int hitPoint)
{
	id = generatorId++;
	lifePoint = lifePoint - hitPoint;
	if (lifePoint <= 0)
	{
		lifePoint = 0;
		life = false;
	}
}

int Warrior::getDistance(const Warrior & other) const
{
	return (int)sqrt(pow(this->location.GetX()-other.location.GetX(),2)
	+ pow(this->location.GetY() - other.location.GetY(), 2));
}

/* add node to  */
void AddNewNode(Node current, int direction)
{
	Node* tmp;
	Point2D* pt;
	vector<Point2D>::iterator gray_it;
	vector<Point2D>::iterator black_it;
	double space_weight = 0.1, wall_weight = 5, weight;
	int dx, dy;

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
	}// switch

	if (direction == ConstValue::UP && current.GetPoint().GetY() > 0 ||
		direction == ConstValue::DOWN && current.GetPoint().GetY() < MSIZE - 1 ||
		direction == ConstValue::LEFT && current.GetPoint().GetX() > 0 ||
		direction == ConstValue::RIGHT && current.GetPoint().GetX() < MSIZE - 1)
	{
		pt = new Point2D(current.GetPoint().GetX() + dx, current.GetPoint().GetY() + dy);
		gray_it = find(gray.begin(), gray.end(), *pt);
		black_it = find(black.begin(), black.end(), *pt);
		if (gray_it == gray.end() && black_it == black.end()) // this is a new point
		{
			// very important to tunnels
			if (maze[current.GetPoint().GetY() + dy][current.GetPoint().GetX() + dx] == ConstValue::WALL)
				weight = wall_weight;
			else weight = space_weight;
			// weight depends on previous weight and wheater we had to dig
			// to this point or not
			tmp = new Node(*pt, target, current.GetG() + weight);
			pq.emplace(*tmp); // insert first node to priority queue
			gray.push_back(*pt); // paint it gray
			// add Parent
			parents.push_back(Parent(tmp->GetPoint(), current.GetPoint(), true));
		}
	}
}

/*
Look for other warrior in room using A* algorithm
use stack::walkingPath to save the steps and move the warrior.
*/
bool Warrior::lookForEnemyInRoom(Warrior & other)
{
	if (currentRoom->locatedInTheRoom(other.getLocation))
	{
		//Variables for A* algorithm
		Node current;
		priority_queue<Node, vector<Node>, CompareNodes> pq;
		vector<Point2D>::iterator gray_it;
		vector<Point2D>::iterator black_it;
		vector <Point2D> gray;
		vector <Point2D> black;
		vector <Parent> parents;
		bool finished = false;

		//A* action
		pq.emplace(this->getLocation());
		while (!finished)
		{
			if (pq.empty())
			{
				cout << "pq should not be empty in this function!\n fnuctin:lookForEnemyInRoom ";
				return false;//Naver need to happend.
			}
			vector<Parent>::iterator itr;
			current = pq.top();
			pq.pop(); // remove it from pq

			 // the target has been found
			if (current.GetH() == 0)
			{
				finished = true;
				// go back to start and enter the steps to walkingPath 
				itr = find(parents.begin(), parents.end(),
					Parent(current.GetPoint(), current.GetPoint(), true));
				walkingPath.push(itr->GetCurrent());
				while (itr->HasParent())
				{
					Point2D tmp_prev = itr->GetPrev();
					Point2D tmp_cur = itr->GetCurrent();
					walkingPath.push(tmp_cur);
					itr = find(parents.begin(), parents.end(),
						Parent(tmp_prev, current.GetPoint(), true));
				}
			}
			
			// check the neighbours
			else 
			{
				// remove current from gray 
				gray_it = find(gray.begin(), gray.end(), current.GetPoint());
				if (gray_it != gray.end())
					gray.erase(gray_it);
				// and paint it black
				black.push_back(current.GetPoint());
				// try to go UP
				if (maze[current.GetPoint().GetY() + 1][[current.GetPoint().GetX()] == TARGET)
					a_star_started = false;

				if (a_star_started && maze[pt->getY() + 1][pt->getX()] == SPACE)
				{ // add it to bestQ
					maze[pt->getY() + 1][pt->getX()] = GRAY;
					parent[pt->getY() + 1][pt->getX()] = pt;

					pt1 = new Point2D(pt->getX(), pt->getY() + 1);// y is i, x is j!!! 

					BestNode* pbn = new BestNode(*pt1, *target);
					bestQ.push(*pbn);

				}
				AddNewNode(current, ConstValue::UP,);
				// try to go DOWN
				AddNewNode(current, ConstValue::DOWN);
				// try to go LEFT
				AddNewNode(current, ConstValue::LEFT);
				// try to go RIGHT
				AddNewNode(current, ConstValue::RIGHT);
			}

		} // while
		
	}
	else  // The enemy in other room.
		return false;
}

/*Serch enemy in the maze
look in the current room, then go to another room and check him.*/
void Warrior::lookForEnemy(Warrior &other)
{
	//1. look for enemy in the current room.
	lookForEnemyInRoom(other);
	//2. calculat the next room the warrior will check.

	//3. go to next room  safely as possible.

	//4. look for enemy in the current room.
}

