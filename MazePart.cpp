#include "MazePart.h"



MazePart::~MazePart()
{
	delete(location);
}

MazePart::MazePart(Point2D* location, int type, double saftyScore) :location(location), type(type), saftyScore(saftyScore)
{
}

void MazePart::resetType()
{
	type = originType;
}
