#pragma once
#include "Point2D.h"
#include "My_Room.h"
#include <stdlib.h>
#include <time.h>

/*the storage activity
increasing life point OR ammo implements in the player class
The storage size is 3X3 by defult.
*/
class Storage
{
private:
	Point2D center; // use like ID and for draw.
	My_Room containedInRoom; 
	bool isAmmo; // true id this ammo storage false if thie medical storage.
	
	//functions
	void setCenterByRoom();
public:
	static const int STORAGE_SIZE = 3;
	
	//functions
	Storage(My_Room containedInRoom, bool isAmmo);
	Storage() {}
	~Storage();
	Point2D getCenter();
	bool getIsAmmo();
};

