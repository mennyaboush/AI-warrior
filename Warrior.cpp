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
	refrashSafetyScore();
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
	int maxDamage = 20;
	
	//Check the ammo.
	if (this->gunsAmmo > 0)
	{
		int distance = getDistance(other);
		
		//check if the warrior no too far
		int damage = maxDamage - distance;
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
	lifePoint = lifePoint - hitPoint;
	if (lifePoint <= 0)
	{
		lifePoint = 0;
		life = false;
	}
}

int Warrior::getDistance(Warrior & other)
{
	return (int)sqrt(pow(this->location.GetX()-other.location.GetX(),2)
	+ pow(this->location.GetY() - other.location.GetY(), 2));
}

