#include "Warrior.h"
#include "Parent.h"
#include "Node.h"

Warrior::Warrior()
{
}

Warrior::Warrior(int maze[ConstValue::MSIZE][ConstValue::MSIZE] ,My_Room room)
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

/*
Look for other warrior in room using A* algorithm
use stack::walkingPath to save the steps and move the warrior.
*/
bool Warrior::lookForEnemyInRoom(Warrior & other)
{
	if (currentRoom->locatedInTheRoom(other.getLocation()))
	{
		//Variables for A* algorithm
		Node current;
		std::priority_queue<Node, std::vector<Node>, CompareNodes> pq;
		std::vector<Point2D>::iterator gray_it;
		std::vector<Point2D>::iterator black_it;
		std::vector <Point2D> gray;
		std::vector <Point2D> black;
		std::vector <Parent> parents;
		bool finished = false;

		//A* action
		pq.emplace(this->getLocation());
		while (!finished)
		{
			if (pq.empty())
			{
				std::cout << "pq should not be empty in this function!\n fnuctin:lookForEnemyInRoom ";
				return false;//Naver need to happend.
			}
			std::vector<Parent>::iterator itr;
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
				Point2D *pt = &current.GetPoint();

				// remove current from gray 
				gray_it = find(gray.begin(), gray.end(), current.GetPoint());
				if (gray_it != gray.end())
					gray.erase(gray_it);
				// and paint it black
				black.push_back(current.GetPoint());
				
				// try to go UP
				if (*(maze[current.GetPoint().GetY() + 1][current.GetPoint().GetX()]) == ConstValue::SPACE)
				{ // add it to pq
					*(maze[pt->GetY() + 1][pt->GetX()]) = ConstValue::GRAY;
					parents.push_back(Parent(Point2D(pt->GetX(), pt->GetY() + 1), *pt, true));
					pq.push(Node(*pt, other.getLocation(), 0));

				}
				// try to go Down
				if (*(maze[current.GetPoint().GetY() - 1][current.GetPoint().GetX()]) == ConstValue::SPACE)
				{ // add it to pq
					*(maze[pt->GetY() - 1][pt->GetX()]) = ConstValue::GRAY;
					parents.push_back(Parent(Point2D(pt->GetX(), pt->GetY() - 1), *pt, true));
					pq.push(Node(*pt, other.getLocation(), 0));

				}

				// try to go LEFT
				if (*(maze[current.GetPoint().GetY()][current.GetPoint().GetX() - 1]) == ConstValue::SPACE)
				{ // add it to pq
					*(maze[pt->GetY()][pt->GetX() - 1]) = ConstValue::GRAY;
					parents.push_back(Parent(Point2D(pt->GetX(), pt->GetY() + 1), *pt, true));
					pq.push(Node(*pt, other.getLocation(), 0));

				}
				// try to go RIGHT
				if (*(maze[current.GetPoint().GetY()][current.GetPoint().GetX() + 1]) == ConstValue::SPACE)
				{ // add it to pq
					*(maze[pt->GetY()][pt->GetX()] + 1) = ConstValue::GRAY;
					parents.push_back(Parent(Point2D(pt->GetX() + 1, pt->GetY()), *pt, true));
					pq.push(Node(*pt, other.getLocation(), 0));
				}
			}
		} 
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

