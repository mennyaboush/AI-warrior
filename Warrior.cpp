#include "Warrior.h"



Warrior::Warrior()
{
}

Warrior::Warrior(int maze[ConstValue::MSIZE][ConstValue::MSIZE] ,Room room)
{
	//Save referance to maze.
	int i, j;
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
