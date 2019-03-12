#pragma once

#include "Point2D.h"
#include "Warrior.h"
#include <iostream>

using namespace std;

class Action
{
public:
	enum eType { RUN, FIND_AMMO, FIND_MED, FIGHT, HURT };

	Action(Warrior& warrior, eType type, int startScore);
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