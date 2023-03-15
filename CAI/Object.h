#pragma once
#include "AABB.h"
#include "Drawable.h"
#include "Actionable.h"
#include "Interactable.h"

enum types { Obj = 100, mveble, sttc, cartype };
enum directions { top = 1, bottom, left, right };


class Object : public Interactable , public Drawable , public Actionable
{
protected:
	AABB space;
	AABB Lastspace;
	Object() {}
	bool destruct = false;
	void destroy() { destruct = true; }
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