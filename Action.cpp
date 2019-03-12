#include "Action.h"

Action::Action(Warrior& warrior, eType type, int startScore): warrior(warrior), type(type), score(startScore)
{

}

void Action::updateScore(int val) 
{
	score += val;
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

//Action &Action::operator=(const Action & other)
//{
//	this -> warrior = other.warrior;
//	this->type = other.type;
//	this->score = other.score;
//	return *this;
//}
