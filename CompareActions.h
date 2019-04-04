#pragma once
#include "Action.h"
#include "Maze.h"

class Warrior;

class CompareActions
{
private:

public:
	CompareActions();
	~CompareActions();
	bool operator( ) (Action* a1, Action* a2);
};

