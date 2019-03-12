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

	const Room& getDestination() { return destination; }
};

