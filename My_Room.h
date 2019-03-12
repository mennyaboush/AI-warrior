#pragma once
#include "Point2D.h"
#include "ConstValue.h"
#include <math.h>
#include "Door.h"
class My_Room
{
public:
	My_Room();
	~My_Room();
	static const int MINIMUM_SIZE = 3;
private:
	Point2D center;
	int width, height;
	std::vector<Door> doors;

public:
	My_Room(const Point2D& center_point, int w, int h);
	Point2D GetCenter() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsOverlap(const My_Room& other) const;
	bool locatedInTheRoom(const Point2D &p) const;
	void addDoor(Door door);
	std::vector<Door> getAllDoors();

	//get the coordinate boundary of the room.
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
};

