#pragma once
#include <memory>

class Point
{
private:
	double X, Y;

public:
	Point() { X = 0, Y = 0; }

	Point(double Xcor, double Ycor);

	Point(const Point& p);

	void operator=(Point& p);

	//Copy function, copies the value of x and y 
	void operator()(double x, double y);

	bool operator==(Point& pnt);

	double GetX() const;

	double GetY() const;

	void SetX(double nx);

	void SetY(double ny);

	~Point() {}
};