#include "Movable.h"
#include <memory>

short Movable::reType()
{
	return mveble;
}

void Movable::PhysicsInit()
{
	setToMove(ph.calcSpeed());
}

void Movable::Accelerate(double x, double y)
{
	ph.AccelerateX(x);
	ph.AccelerateY(y);
}

std::shared_ptr<Point> Movable::MovementVector()
{
	Point ls = *Lastspace.getCenter().get();
	Point cs = *space.getCenter().get();
	double x_diff = cs.GetX() - ls.GetX();
	double y_diff = cs.GetY() - ls.GetY();
	return std::make_shared<Point>(x_diff,y_diff);
}

void Movable::setToMove(PhysicsStats ph)
{
	Move(ph.xspeed, ph.yspeed);
}

void Movable::PhysicsIntersection(double overlap ,short direction)
{
	if (direction == top)
	{
		Move(0, -overlap);
		ph.intersection(0, 1, top);
	}
	if (direction == bottom)
	{
		Move(0, overlap);
		ph.intersection(0, 1, bottom);
	}
	if (direction == left)
	{
		Move(-overlap-2, 0);
		ph.intersection(1, 0, left);
	}
	if (direction == right)
	{
		Move(overlap+2, 0);
		ph.intersection(1, 0, right);
	}
}