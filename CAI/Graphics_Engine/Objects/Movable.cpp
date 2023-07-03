#include "Movable.h"
#include <memory>

short Movable::reType()
{
	return mveble;
}

void Movable::PhysicsInit()
{
	setToMove(_ph_.calcSpeed());
}

void Movable::Accelerate(double x, double y)
{
	_ph_.AccelerateX(x);
	_ph_.AccelerateY(y);
}

std::shared_ptr<Point> Movable::MovementVector()
{
	Point ls = Lastspace.getCenter();
	Point cs = space.getCenter();
	double x_diff = cs.GetX() - ls.GetX();
	double y_diff = cs.GetY() - ls.GetY();
	return std::make_shared<Point>(x_diff,y_diff);
}

void Movable::setToMove(PhysicsStats _ph_)
{
	move(_ph_.xspeed, _ph_.yspeed);
}

void Movable::PhysicsIntersection(double overlap ,short direction)
{
	if (direction == top)
	{
		move(0, -overlap);
		_ph_.intersection(0, 1, top);
	}
	if (direction == bottom)
	{
		move(0, overlap);
		_ph_.intersection(0, 1, bottom);
	}
	if (direction == left)
	{
		move(-overlap-2, 0);
		_ph_.intersection(1, 0, left);
	}
	if (direction == right)
	{
		move(overlap+2, 0);
		_ph_.intersection(1, 0, right);
	}
}