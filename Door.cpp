#include "Door.h"

Door::Door(Room& current, Room& destination): current(current), destination(destination)
{
}

Door::~Door()
{
}

/*Check if we allrady visit in the destination of the door.
visit? pass the door. else serch.
*/
bool Door::isDestinationDoor(const Room& destination) const
{
	static set<Room *> visited;
	if (&(this->destination) == &destination)
	{
		visited.clear();
		return true;
	}
	visited.insert(&this->current);
	if(*(visited.find((Room*)&destination)  )!= &destination) //== visited.end())
		return (this->destination).isDestionationRoom(destination);
	return false;
}

