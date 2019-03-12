#pragma once
#include "Room.h"
class Door
{
private:
	Room &current;
	Room &destination;
	
public:
	Door(Room& current, Room& destination);
	~Door();

	//check if the door get the destination.
	bool isDestinationDoor(const Room& destination) const;
	const Room& getDestination() { return destination; }
};

