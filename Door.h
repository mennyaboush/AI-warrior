#pragma once

#include <vector>
#include "Point2D.h"
#include "My_Room.h"
//using namespace std;
class Door
{

private:
 	My_Room current;
	std::vector <My_Room*> destination;
	Point2D location;
	

public:
	Door();
	Door(My_Room current, Point2D location);
	~Door();
};

