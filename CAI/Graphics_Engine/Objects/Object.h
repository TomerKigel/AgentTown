#pragma once
#include "../../Graphics_Engine/Space/AABB.h"
#include "../../Graphics_Engine/Interfaces/Interface_Actionable.h"
#include "../../Graphics_Engine/Interfaces/Interface_Drawable.h"
#include "../../Graphics_Engine/Interfaces/Interface_Interactable.h"


enum types { Obj = 100, mveble, sttc, cartype };
enum directions { top = 1, bottom, left, right };


class Object : public Interface_Interactable , public Interface_Drawable , public Interface_Actionable
{
protected:
	int id;

	AABB space;
	AABB Lastspace;
	Object() {}
	bool destruct = false;
public:
	virtual void destroy() { destruct = true; }
	virtual short reType() { return Obj; }
	bool isUpForDestruction() { return destruct; }
	virtual void draw() {};

	int get_id()
	{
		return id;
	}

	void set_id(int ID)
	{
		id = ID;
	}
	~Object() {}

	virtual AABB* getAABB()
	{
		return &space;
	}

	virtual Point getCenter()
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