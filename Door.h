#pragma once
#include "Room.h"
class Door
{
private:
	Room current;
	Room *destination;
	

public:
	Door();
	~Door();
};

