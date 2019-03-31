#pragma once

#include "Point2D.h"
#include "Warrior.h"
#include <iostream>
class Warrior;
using namespace std;
enum eType { RUN, FIND_AMMO, FIND_MED, FIGHT, HURT };

/*This class conatin priorityQ
with all the action.
the Q get update regularly and the top action is the action the warrior shoulde do */
class Action
{
public:
	Action(Warrior& warrior, eType type);
	Action &operator=(const Action & other) = delete;

private:
	static const int NUM_OF_TYPES = 4;
	
	Warrior& warrior;
	int score;
	eType type;
public:
	void updateScore(int val);
	int getScore() const;
	Warrior& getWarrior() const;
	eType getType() const;
};