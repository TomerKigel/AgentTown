#pragma once

#include <SFML\Graphics.hpp>
#include "../../Graphics_Engine/Physics/Physics.h"
#include "../../Graphics_Engine/Objects/Object.h"


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
	void setToMove(PhysicsStats _ph_);

protected:
	Physics _ph_;

	Movable() { Lastspace = space; }

public:
	
	virtual void move(double xspd, double yspd) = 0;

	virtual short reType();

	void PhysicsInit();

	void PhysicsIntersection(double overlap, short direction);

	void Accelerate(double x, double y);

	std::shared_ptr<Point> MovementVector();

	~Movable() {}
};

