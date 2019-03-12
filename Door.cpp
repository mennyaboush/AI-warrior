#include "Door.h"



Door::Door()
{
}


/*Need to add destionation!!! */
Door::Door(My_Room current, Point2D location)
{
	this->current = current;
	this->location = location;
}

Door::~Door()
{
}
