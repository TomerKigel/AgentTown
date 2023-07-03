#pragma once
#include "../../Graphics_Engine//Space/AABB.h"

class Interface_Interactable
{
public:
	virtual AABB* getAABB() = 0;
	virtual void setAABB(AABB &aabb) = 0;
	virtual Point getCenter() = 0 ;
	virtual bool InteractWith(Interface_Interactable* obj, short type) { return false; };
	virtual AABB* getLastSpace() = 0;
	virtual void SpaceBack() = 0;
	virtual void refreshLastSpace() = 0;
	virtual short reType() = 0;
};