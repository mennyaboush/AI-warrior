#pragma once

#include "Point2D.h"
#include <iostream>

class Warrior;
using namespace std;

/*This class conatin priorityQ
with all the action.
the Q get update regularly and the top action is the action the warrior shoulde do */
class Action
{
public:
	enum eType { RUN, FIND_AMMO, FIND_MED, FIGHT, HURT };
	
	Action(Warrior& warrior, eType type);
	Action &operator=(const Action & other) = delete;

	void updateScore(int val);
	int getScore() const { return score; };
	Warrior& getWarrior() const;
	eType getType() const;
	
	/*Calculate the Score by the action type
	and the parameters we can get from the warrior and need for the calculate function.*/
	double calculateScore(Action::eType type, Warrior &warrior);
	
private:
	static const int NUM_OF_TYPES = 4;
	const double MAX_SCORE = 100;//calculate function return value in the range [0,100]


	Warrior& warrior;
	int score;
	eType type;

	double calculateScoreRun(Warrior& w);
	double calculateScoreFindAmmo(Warrior& w);
	double calculateScoreFindMed(Warrior& w);
	double calculateScoreFight(Warrior& w);
	double calculateScoreHurt(Warrior& w);

public:
};