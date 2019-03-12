#include "My_Room.h"



My_Room::My_Room()
{
}


My_Room::~My_Room()
{
}


My_Room::My_Room(const Point2D& center_point, int w, int h)
{
	center = center_point;
	width = w;
	height = h;
}


Point2D My_Room::GetCenter() const
{
	return center;
}


int My_Room::GetWidth() const
{
	return width;
}


int My_Room::GetHeight() const
{
	return height;
}


bool My_Room::IsOverlap(const My_Room& other) const
{
	return abs(center.GetX()-other.GetCenter().GetX())
		< (width+other.width)/2+5 && abs(center.GetY() - 
			other.GetCenter().GetY()) < (height+other.height)/2+5  ;
}

bool My_Room::locatedInTheRoom(const Point2D & p) const
{
	return (p.GetX() <= getRight() && p.GetX() >= getLeft()
		&& p.GetY() <= getBottom() && p.GetY() >= GetHeight());
}

void My_Room::addDoor(Door door)
{
	doors.push_back(door);
}

std::vector<Door> My_Room::getAllDoors()
{
	 return doors; 
}

int My_Room::getLeft() const
{
	int left = this->GetCenter().GetX() - this->GetWidth() / 2;
	if (left < 0)
		return 0;
	else
		return left;
}

int My_Room::getRight() const
{
	int right = this->GetCenter().GetX() + this->GetWidth() / 2;
	if (right >= ConstValue::MSIZE)
		return ConstValue::MSIZE - 1 ;
	return right;
}

int My_Room::getTop() const
{
	int top = this->GetCenter().GetY() - this->GetHeight() / 2;
	if(top < 0)
		return 0;
	else 
		return top;
}

int My_Room::getBottom() const
{
	int bottom = this->GetCenter().GetY() + this->GetHeight() / 2;
	if (bottom >= ConstValue::MSIZE) return bottom = ConstValue::MSIZE - 1;
	else
		return bottom;
}
