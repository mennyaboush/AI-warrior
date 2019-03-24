#include "Point2D.h"
#include "ConstValue.h"


Point2D::Point2D()
	: x(0)
{
}


Point2D::~Point2D()
{
}


Point2D::Point2D(int x, int y,int *maze[ConstValue::MSIZE][ConstValue::MSIZE])
{
	this->x = x;
	this->y = y;
	this->saftyScore = calcuateSeftyScore(x, y, maze);
}


int Point2D::GetX() const
{
	return x;
}


int Point2D::GetY() const
{
	return y;
}


bool Point2D::operator==(const Point2D& other)
{
	return x==other.x && y== other.y;
}

/*calcuateSeftyScore is a static function hoe calculate the safty score
by the closest area to the specific point(p)*/
double Point2D::calcuateSeftyScore(Point2D & p, int *maze[ConstValue::MSIZE][ConstValue::MSIZE])
{
	calcuateSeftyScore(p.GetX(), p.GetY(), maze);
}


/*calcuateSeftyScore is a static function hoe calculate the safty score
by the closest area to the specific point values*/
double Point2D::calcuateSeftyScore(int x, int y, int * maze[ConstValue::MSIZE][ConstValue::MSIZE])
{
	//1. declarete Varieble
	const int ALL_AREA = 8; //Chack area of 3X3 
	int safeAreas = 0;
	int score = 0, i, j;
	//2. run on the squares surrounding the point and same the walles.
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (*(maze[j][i]) == ConstValue::WALL)
				safeAreas++;
		}
	}
	//3. calculate the number how safe this point
	return (ALL_AREA - safeAreas) / ALL_AREA;
}


