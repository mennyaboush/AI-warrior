#pragma once
#include "Point2D.h"
#include "ConstValue.h"
#include <math.h>

class Room
{
public:
	Room();
	~Room();
	static const int MINIMUM_SIZE = 3;
private:
	Point2D center;
	int width, height;
public:
	Room(const Point2D& center_point, int w, int h);
	Point2D GetCenter() const;
	int GetWidth();
	int GetHeight();
	bool IsOverlap(const Room& other);
	
	//get the coordinate boundary of the room.
	int getLeft();
	int getRight();
	int getTop();
	int getBottom();
};

