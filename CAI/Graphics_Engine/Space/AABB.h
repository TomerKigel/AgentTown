#pragma once

#include "Point.h"
#include <memory>

class AABB : public std::enable_shared_from_this<AABB>
{
private:
	// T = top 
	// B = bottom
	// L = left 
	// R = right 
	Point TL;
	Point BR;

public:

	AABB() {}

	AABB(double tlx, double tly, double brx, double bry);

	AABB(Point tl, Point br);

	Point getCenter();

	int GetLen();

	int GetWid();

	Point GetTL();

	Point GetBR();

	bool operator==(const AABB& range) const;

	bool operator<(AABB& range);

	static bool cmpPtN(AABB* range, AABB* secRange);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB is 1 pixel away from the range sent to the function			
	//\param range   AABB for comparison												
	///////////////////////////////////////////////////////////////////////////////////////
	int operator-=(AABB& range);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB intersects with the range of the given parameter			
	//\param range   AABB for comparison												
	///////////////////////////////////////////////////////////////////////////////////////
	void operator*=(double f);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB contains a given point				
	//\param pnt   point to find in the AABB's range												
	///////////////////////////////////////////////////////////////////////////////////////
	bool isContaining(Point pnt) const;

	void operator=(AABB& origin);

	////////////////////////////////////////////////////////////////////////////////////////
	//Copy Function														
	//\brief  Sets AABB's values to the values of a,b as origin			
	//\param a   top left x coordinate to copy from
	//\param b   bottom right y coordinate to copy from										
	///////////////////////////////////////////////////////////////////////////////////////
	void operator()(double top_left_x, double top_left_y, double bottom_right_x, double bottom_right_y);

	////////////////////////////////////////////////////////////////////////////////////////
	//Copy Function														
	//\brief  Sets AABB's values to the values of a,b as origin			
	//\param a   top left x coordinate to copy from
	//\param b   bottom right y coordinate to copy from										
	///////////////////////////////////////////////////////////////////////////////////////
	void operator()(Point top_left, Point bottom_right);

	////////////////////////////////////////////////////////////////////////////////////////
	//Mutator Function														
	//\brief  Sets TL values				
	//\param x   x coordinate of TL		
	//\param y   y coordinate of TL	
	///////////////////////////////////////////////////////////////////////////////////////
	void SetTL(double x, double y);

	////////////////////////////////////////////////////////////////////////////////////////
	//Mutator Function														
	//\brief  Sets BR values				
	//\param x   x coordinate of BR	
	//\param y   y coordinate of BR												
	///////////////////////////////////////////////////////////////////////////////////////
	void SetBR(double x, double y);


	////////////////////////////////////////////////////////////////////////////////////////
	//Intersection helper function												
	//\brief  returns where an object is in relation to another. (top,bottom,left or right)			
	//\param t   AABB of the object to be tested 											
	///////////////////////////////////////////////////////////////////////////////////////
	short WIRTTO(AABB other);

	////////////////////////////////////////////////////////////////////////////////////////
	//Intersection helper function												
	//\brief  returns a value for either x or y axis amount of overlap,depending on direction 			
	//\param t			 AABB of the object to be tested 	
	//\param direction   where is t parameter in relation current object(derived from WIRTTO)	
	///////////////////////////////////////////////////////////////////////////////////////
	double Overlap(AABB t, short direction);


	double GetLeft();

	double GetRight();

	double GetTop();

	double GetBottom();

	~AABB() {}
};
