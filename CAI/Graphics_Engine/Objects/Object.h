#pragma once
#include "../../Graphics_Engine/Space/AABB.h"
#include "../../Graphics_Engine/Interfaces/Actionable.h"
#include "../../Graphics_Engine/Interfaces/Drawable.h"
#include "../../Graphics_Engine/Interfaces/Interactable.h"


enum types { Obj = 100, mveble, sttc, cartype };
enum directions { top = 1, bottom, left, right };


class Object : public Interactable , public Drawable , public Actionable
{
protected:
	AABB space;
	AABB Lastspace;
	Object() {}
	bool destruct = false;
	virtual void destroy() { destruct = true; }
public:
	virtual short reType() { return Obj; }
	bool isUpForDestruction() { return destruct; }
	virtual void draw() {};
	~Object() {}

	virtual AABB* getAABB()
	{
		return &space;
	}

	virtual std::shared_ptr<Point> getCenter()
	{
		return space.getCenter();
	}


	virtual void setAABB(AABB &aabb)
	{
		space = aabb;
	}

	virtual AABB* getLastSpace()
	{
		return &Lastspace;

	}

	virtual void SpaceBack()
	{
		space = Lastspace;
	}

	virtual void refreshLastSpace()
	{
		Lastspace = space;
	}
};