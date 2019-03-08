#include "Warrior.h"
#include "Action.h"

Warrior::Warrior(int ***maze, Room room): location(room.GetCenter()) 
{
	//Save referance to maze.
	int i, j;
	
	this->maze = maze;

	/*for (i = 0; i < ConstValue::MSIZE; i++) {
		*(this->maze)[i] = maze[i];
	}*/

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

void Warrior::moveWarrior()
{
	Action toDo = actionQueue.top();	// RUN, FIND_AMMO, FIND_MED, FIGHT
	actionQueue.pop();

	switch (toDo.getType())
	{
	case Action::FIGHT:
		// do 20 steps in the derection of the other warrior and fight if close enought
		break;
	case Action::RUN:
		// do 20 steps in opposite derections of the other warrior
		//runAway();
		break;
	case Action::FIND_AMMO:
		// go through rooms and look for ammo
		//lookForMedicalStorage();
		break;
	case Action::FIND_MED:
		// go through rooms and look for med
		//lookForAmmoStorage();
		break;
	}
}

void lookForTarget(Point2D target)
{
	
}

//	bn = (*bestQ).top();
//	(*bestQ).pop();
//	pt = new Point2D(bn.point); // need to delete the allocation
//
//	// change current location
//	if (maze[pt->getY()][pt->getX()] == SPACE)
//		maze[pt->getY()][pt->getX()] = PAKMAN;
//
//	else if (maze[pt->getY()][pt->getX()] == COIN)
//	{
//		maze[pt->getY()][pt->getX()] = PAKMAN_COIN;
//	}
//
//	int pakmanLocation = lookForPakman(pt->getX(), pt->getY());
//	if (pakmanLocation != NOT_FOUND)
//	{
//		gameIsOn = false;
//		getMonsterPath(pt, parent, monsterPath);
//		return;
//	}
//
//	// UP
//	if (maze[pt->getY() + 1][pt->getX()] == SPACE || maze[pt->getY() + 1][pt->getX()] == COIN)
//	{
//		parent[pt->getY() + 1][pt->getX()] = pt;
//		pt1 = new Point2D(pt->getX(), pt->getY() + 1); // y is i, x is j!!! 
//
//		(*bestQ).push(BestNode(*pt1, *pakman));
//		delete(pt1);
//	}
//
//	// DOWN
//	if (maze[pt->getY() - 1][pt->getX()] == SPACE || maze[pt->getY() - 1][pt->getX()] == COIN)
//	{
//		parent[pt->getY() - 1][pt->getX()] = pt;
//		pt1 = new Point2D(pt->getX(), pt->getY() - 1);// y is i, x is j!!! 
//		(*bestQ).push(BestNode(*pt1, *pakman));
//		delete(pt1);
//	}
//
//	// RIGHT
//	if (maze[pt->getY()][pt->getX() + 1] == SPACE || (maze[pt->getY()][pt->getX() + 1]) == COIN)
//	{
//		parent[pt->getY()][pt->getX() + 1] = pt;
//		pt1 = new Point2D(pt->getX() + 1, pt->getY());// y is i, x is j!!! 
//		(*bestQ).push(BestNode(*pt1, *pakman));
//		delete(pt1);
//	}
//
//	// LEFT
//	if (gameIsOn && maze[pt->getY()][pt->getX() - 1] == SPACE || gameIsOn && maze[pt->getY()][pt->getX() - 1] == COIN)
//	{
//		parent[pt->getY()][pt->getX() - 1] = pt;
//		pt1 = new Point2D(pt->getX() - 1, pt->getY());// y is i, x is j!!! 
//		(*bestQ).push(BestNode(*pt1, *pakman));
//		delete(pt1);
//	}
//
//	if (!(*resetPath)) // target was found
//		getMonsterPath(pt, parent, monsterPath);
//}