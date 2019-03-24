#pragma once
#include "Point2D.h"

class PieceOfLand
{
private:
	class Point2D;
	Point2D *location = nullptr;
	double saftyScore;
	int type;
public:
	PieceOfLand();
	~PieceOfLand() { delete(location); };
	PieceOfLand(Point2D &location, int type, double saftyScore);

	Point2D* getLocation() const { return location; }
	double getSaftScore() const { return saftyScore; }
	int getType() const { return type; }
	void setLocation(Point2D &location) { this->location = &location; }
	void setSaftyScore(double saftyScore) { this->saftyScore = saftyScore; }
	void setType(int type) { this->type = type; }

};
