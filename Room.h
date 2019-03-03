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
	int GetWidth() const;
	int GetHeight() const;
	bool IsOverlap(const Room& other) const;
	bool locatedInTheRoom(const Point2D &p) const;

	//get the coordinate boundary of the room.
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
};

