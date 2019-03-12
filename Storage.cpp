#include "Storage.h"



void Storage::setCenterByRoom()
{
	//srand(time(0));
	int w = this->containedInRoom.getRight() - this->containedInRoom.getLeft();
	int h = this->containedInRoom.getBottom() - this->containedInRoom.getTop();
	w = rand()%w + this->containedInRoom.getLeft();
	h = rand() % h + this->containedInRoom.getTop();
	this->center = Point2D(w, h);
}

Storage::Storage(My_Room containedInRoom, bool isAmmo)
{
	this->containedInRoom = containedInRoom;
	this->isAmmo = isAmmo;
	setCenterByRoom();
}


Storage::~Storage()
{
}

Point2D Storage::getCenter()
{
	return this->center;
}

bool Storage::getIsAmmo()
{
	return isAmmo;
}
