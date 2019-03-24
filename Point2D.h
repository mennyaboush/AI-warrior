#pragma once
#include "ConstValue.h"
class Point2D
{
public:
	Point2D();
	~Point2D();
private:
	int x;
	int y;
	double saftyScore;
public:
	Point2D(int x, int y, int *maze[ConstValue::MSIZE][ConstValue::MSIZE]);
	int GetX() const;
	int GetY() const;
	int getSaftyScore() const { return saftyScore; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	bool operator==(const Point2D& other);
	/*calcuateSeftyScore is a static function hoe calculate the safty score by the closest area to the specific point*/
	static double calcuateSeftyScore(Point2D &p,int *maze[ConstValue::MSIZE][ConstValue::MSIZE] );
	/*calcuateSeftyScore is a static function hoe calculate the safty score by the closest area to the specific point values*/
	static double calcuateSeftyScore(int x,int y, int *maze[ConstValue::MSIZE][ConstValue::MSIZE]);
};

