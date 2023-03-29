#pragma once
#include "../Objects/Object.h"
#include "SFML\Graphics.hpp"
#include <vector>

class QuadTree
{
private:
	QuadTree* root;
	short depth;
	QuadTree* parent;
	QuadTree* node[4];
	std::vector<Object*> itemlist;
	const static int maxitem = 15;
	AABB Range;
	AABB LooseRange;
	QuadTree() 
	{
		depth = 0;
		for (size_t i = 0; i < 4; i++)
		{
			node[i] = nullptr;
		}
		parent = nullptr;
		root = nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//QuadTree devider			
	//
	//\brief   Devides the current level of the quadtree into 4 identical quadspaces												
	////////////////////////////////////////////////////////////////////////////////////////

	void split();

public:
	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor			
	//
	//\brief   sets the scope of the quadtree to the range of a given AABB
	//
	//\param range   an AABB scope for the Quadtree														
	////////////////////////////////////////////////////////////////////////////////////////


	QuadTree(AABB range, QuadTree* r = nullptr, short d = 0, QuadTree* p = nullptr);


	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor			
	//
	//\brief   sets the scope of the quadtree using 2 points
	//
	//\param tl   Top Left Point														
	//\param br   Bottom Right Point																									
	////////////////////////////////////////////////////////////////////////////////////////


	QuadTree(Point tl, Point br, QuadTree* r = nullptr, short d = 0, QuadTree* p = nullptr);


	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor				
	//
	//\brief   sets the scope of the quadtree using 4 coordiantes, the first two parameters describe the first point 
	// while the the third and forth parametrs describe the second point	
	//
	//\param tlx   Top Left X cooridante														
	//\param tly   Top Left Y cooridante														
	//\param brx   Bottom Right X cooridante												    
	//\param brx   Bottom Right Y cooridante													
	////////////////////////////////////////////////////////////////////////////////////////


	QuadTree(double Tlx, double Tly, double Brx, double Bry, QuadTree* r = nullptr, short d = 0, QuadTree* p = nullptr);


	////////////////////////////////////////////////////////////////////////////////////////
	//Insertion																	
	//\brief   Inserts an item into the QuadTree	
	//\param item   a pointer to an item																									
	////////////////////////////////////////////////////////////////////////////////////////
	bool insert(Object* item);

	////////////////////////////////////////////////////////////////////////////////////////
	//QuadTree Range Query			
	//
	//\brief   Find all items in a given range within the Quadtree
	//
	//\param   AABB range to query
	//\param   tv returns vector of found items within range
	////////////////////////////////////////////////////////////////////////////////////////

	std::vector<Object*> QueryRange(AABB range, std::vector<Object*>& tv);

	////////////////////////////////////////////////////////////////////////////////////////
	//QuadTree Range Query			
	//
	//\brief   Find all items in a given range within the Quadtree
	//
	//\param   AABB range to query
	//\param   tv returns vector of found items within range
	////////////////////////////////////////////////////////////////////////////////////////

	void QueryRangeByObj(std::vector<Object>* lst);

	////////////////////////////////////////////////////////////////////////////////////////
	//QuadTree Query Nodes			
	//
	//\brief   Querys all nodes one by one
	////////////////////////////////////////////////////////////////////////////////////////

	void QueryNodes();

	void CleanTree();

	~QuadTree();

	void tdraw(sf::RenderWindow& window_);

};