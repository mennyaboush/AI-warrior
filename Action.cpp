#include "Action.h"

Action::Action(Warrior& warrior, eType type): warrior(warrior), type(type)
{
}

void Action::updateScore(int val) 
{
	if (val >= 0 && val <= 100)
		this->score = val;
	else
		throw exception("The function Action::updateScore get invalide value");
}

Warrior& Action::getWarrior() const
{
	return warrior;
}

int Action::getScore() const
{
	return score;
}

Action::eType Action::getType() const
{
	return type;
}

