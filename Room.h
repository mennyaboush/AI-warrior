#pragma once
#include "Point2D.h"
#include "ConstValue.h"
#include <math.h>
#include <vector>
#include <set>

class Door;

using namespace std;

class Room
{
public:
	Room();
	~Room();
	static const int MINIMUM_SIZE = 3;
	static const int MAX_OBSACLES = 5;
private:
	int id;
	Point2D *center;
	vector<Door*> doors;

	int width, height;
public:
	Room(int id, const Point2D& center_point, int w, int h);
	Point2D &GetCenter() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsOverlap(const Room& other);
	bool locatedInTheRoom(const Point2D &p) const;
	bool isDestionationRoom(const Room &destionation) const;
	bool canBeObsacle(Point2D& p);
	bool notBorder(Point2D& p) const;

	//get the coordinate boundary of the room.
	int getId() { return id; }
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
	vector<Door*> getDoors() const;
	void addDoor(Door& door);
	void currectPointToBeInRoom(Point2D &p);
	Point2D& getRandomPointInRoom();
	
};

