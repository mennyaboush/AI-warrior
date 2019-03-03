#include "Warrior.h"


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
	this->currentRoom = room;
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

/*Look for other warrior in room using A* algorithm*/
bool Warrior::lookForEnemyInRoom(Warrior & other)
{
	if ()
	priority_queue<Node, vector<Node>, CompareNodes> pq;
	
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

