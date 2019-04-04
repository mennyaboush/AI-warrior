#pragma once
class Point2D
{
public:
	Point2D();
	~Point2D();
private:
	int x;
	int y;
public:
	Point2D(int x, int y);
	int GetX() const;
	int GetY() const;
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	bool operator==(const Point2D& other);
	bool operator!=(const Point2D& other);
};

