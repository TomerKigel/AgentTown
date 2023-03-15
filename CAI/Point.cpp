#include "Point.h"

Point::Point(double Xcor, double Ycor)
{
	X = Xcor;
	Y = Ycor;
}

Point::Point(const Point& p)
{
	X = p.GetX();
	Y = p.GetY();
}

void Point::operator=(Point& p)
{
	X = p.GetX();
	Y = p.GetY();
}

void Point::operator()(double x, double y)
{
	X = x;
	Y = y;
}

bool Point::operator==(Point& pnt)
{
	if (X == pnt.GetX() && Y == pnt.GetY())
		return true;
	return false;

}

double Point::GetX() const
{
	return X;
}

double Point::GetY() const
{
	return Y;
}

void Point::SetX(double nx)
{
	X = nx;
}

void Point::SetY(double ny)
{
	Y = ny;
}
