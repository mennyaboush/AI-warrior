#include "CompareActions.h"
#include "Action.h"


CompareActions::CompareActions()
{
}


CompareActions::~CompareActions()
{
}


bool CompareActions::operator( )(const Action& a1, const Action& a2)
{
	return a1.getScore() > a2.getScore();
}