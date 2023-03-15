#pragma once

#include "SFML\Graphics.hpp"
#include "Object.h"
#include "Physics.h"


class Movable : public Object
{
private:
	////////////////////////////////////////////////////////////////////////////////////////
	//virtual mutator function			
	//
	//\brief   moves the object in a direction
	//
	//\param xspd   pixels to move on the x axis		
	//\param yspd   pixels to move on the y axis	
	////////////////////////////////////////////////////////////////////////////////////////
	void setToMove(PhysicsStats ph);

protected:
	Physics ph;
	

	Movable() { Lastspace = space; }

public:
	
	virtual void Move(double xspd, double yspd) = 0;

	virtual short reType();

	void PhysicsInit();

	void PhysicsIntersection(double overlap, short direction);

	void Accelerate(double x, double y);

	std::shared_ptr<Point> MovementVector();

	~Movable() {}
};

