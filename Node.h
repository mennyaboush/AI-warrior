#pragma once

#include "Point2D.h"
class Node
{
public:
	Node();
	~Node();
private:
	Point2D point, target;
	double g;
	double saftyScore = 0;
public:
	/*GetF return the safty + the distance to the target location*/
	double GetF() const;
	/*getS return a value who represent the safty of this point. */
	double getS(){ return saftyScore; }
	/*getDistance return the distance from the current point to the target point*/
	double getDistance();
	
	double GetG() const;
	double GetH() const;
	Node(const Point2D& p, const Point2D& t, double saftyScore);
	Point2D GetPoint();
};

