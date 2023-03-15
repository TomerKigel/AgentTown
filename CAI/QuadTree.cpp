#include "QuadTree.h"
#include <iostream>

QuadTree::QuadTree(AABB range, QuadTree* r, short d, QuadTree* p)
{
	//Root and parent Settings
	if (r == nullptr)
		root = this;
	else
		root = r;

	parent = p;

	//Depth Settings
	depth = d + 1;

	//Node initilazing
	for (short i = 0; i < 4; i++)
	{
		node[i] = nullptr;
	}

	//Scope settings
	Range = range;
	LooseRange = Range;
	LooseRange *= 2;
}

QuadTree::QuadTree(Point tl, Point br, QuadTree* r, short d, QuadTree* p)
{
	//Root and parent Settings
	if (r == nullptr)
		root = this;
	else
		root = r;

	parent = p;

	//Depth Settings
	depth = d + 1;

	//Node initilazing
	for (short i = 0; i < 4; i++)
	{
		node[i] = nullptr;
	}

	//Scope settings
	Range(tl, br);
	LooseRange = Range;
	LooseRange *= 2;
}

QuadTree::QuadTree(double Tlx, double Tly, double Brx, double Bry, QuadTree* r, short d, QuadTree* p)
{
	//Root and parent Settings
	if (r == nullptr)
		root = this;
	else
		root = r;

	parent = p;

	//Depth Settings
	depth = d + 1;

	//Node initilazing
	for (short i = 0; i < 4; i++)
	{
		node[i] = nullptr;
	}

	//Scope settings
	Range(Tlx, Tly, Brx, Bry);
	LooseRange = Range;
	LooseRange *= 2;
}

bool QuadTree::insert(Object* item)
{
	Point p = *item->getCenter().get();
	if (Range.isContaining(p))
	{
		if (item->getAABB()->GetLen() <= LooseRange.GetLen() &&
			item->getAABB()->GetWid() <= LooseRange.GetWid())
		{
			if (node[0] != nullptr)
			{
				if (!node[0]->insert(item))
					if (!node[1]->insert(item))
						if (!node[2]->insert(item))
							node[3]->insert(item);
			}
			else if (itemlist.size() < maxitem)
			{
				itemlist.push_back(item);
			}
			else if (Range.GetLen() < 120)
			{
				itemlist.push_back(item);
				return true;
			}
			else
			{
				split();
				return insert(item);
			}
		}
		else
		{
			parent->itemlist.push_back(item);
			return true;
		}
		return true;
	}
	else
		return false;
}

void QuadTree::split()
{
	node[0] = new QuadTree(Range.GetTL().GetX(),
		Range.GetTL().GetY(),
		(Range.GetBR().GetX() + Range.GetTL().GetX()) / 2,
		(Range.GetBR().GetY() + Range.GetTL().GetY()) / 2,
		root,
		depth,
		this
	);
	node[1] = new QuadTree((Range.GetBR().GetX() + Range.GetTL().GetX()) / 2,
		Range.GetTL().GetY(),
		Range.GetBR().GetX(),
		(Range.GetBR().GetY() + Range.GetTL().GetY()) / 2,
		root,
		depth,
		this
	);
	node[2] = new QuadTree(Range.GetTL().GetX(),
		(Range.GetBR().GetY() + Range.GetTL().GetY()) / 2,
		(Range.GetBR().GetX() + Range.GetTL().GetX()) / 2,
		Range.GetBR().GetY(),
		root,
		depth,
		this
	);
	node[3] = new QuadTree((Range.GetBR().GetX() + Range.GetTL().GetX()) / 2,
		(Range.GetBR().GetY() + Range.GetTL().GetY()) / 2,
		Range.GetBR().GetX(),
		Range.GetBR().GetY(),
		root,
		depth,
		this
	);
	std::vector<Object*> til = itemlist;
	itemlist.clear();
	itemlist.shrink_to_fit();
	for (short i = 0; i < til.size(); i++)
	{
		insert(til.at(i));
	}
}

std::vector<Object*> QuadTree::QueryRange(AABB range, std::vector<Object*>& tv)
{
	if (!(Range == range))
		return tv;
	else {
		for (short i = 0; i < itemlist.size(); i++)
		{
			if (*itemlist[i]->getAABB() == range)
				tv.push_back(itemlist[i]);
		}
	}

	if (node[0] == nullptr)
		return tv;

	node[0]->QueryRange(range, tv);
	node[2]->QueryRange(range, tv);
	node[1]->QueryRange(range, tv);
	node[3]->QueryRange(range, tv);

	return tv;
}


void QuadTree::QueryNodes()
{
	if (node[0] != nullptr) {
		node[0]->QueryNodes();
		node[1]->QueryNodes();
		node[2]->QueryNodes();
		node[3]->QueryNodes();
	}
	else if (itemlist.size() > 0)
	{
		std::vector<Object*> testset;
		root->QueryRange(LooseRange, testset);
		for (short i = 1; i < testset.size(); i++)
		{
			for (short p = 0; p < i; p++)
			{
				if (*testset[i]->getAABB() == *testset[p]->getAABB())
				{
					testset[i]->InteractWith(testset[p], testset[p]->reType());
					testset[p]->InteractWith(testset[i], testset[i]->reType());
				}
			}

		}
	}
}
void QuadTree::QueryRangeByObj(std::vector<Object>* lst)
{
	std::vector<Object*> testset;
	for (short i = 0; i < lst->size(); i++)
	{
		root->QueryRange(*lst->at(i).getAABB(), testset);
		for (short p = 0; p < i; p++)
		{
			if (*testset[i]->getAABB() == *testset[p]->getAABB())
			{
				testset[i]->InteractWith(testset[p], testset[p]->reType());
				testset[p]->InteractWith(testset[i], testset[i]->reType());
			}
		}
	}
}

QuadTree::~QuadTree()
{

}

void QuadTree::tdraw(sf::RenderWindow& window_)
{
	if (node[0] != nullptr) {
		node[0]->tdraw(window_);
		node[1]->tdraw(window_);
		node[2]->tdraw(window_);
		node[3]->tdraw(window_);
	}

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(Range.GetTL().GetX(), Range.GetBR().GetY())),
		sf::Vertex(sf::Vector2f(Range.GetTL().GetX(), Range.GetTL().GetY()))
	};
	sf::Vertex linee[] =
	{
		sf::Vertex(sf::Vector2f(Range.GetTL().GetX(), Range.GetBR().GetY())),
		sf::Vertex(sf::Vector2f(Range.GetBR().GetX(), Range.GetBR().GetY()))
	};
	sf::Vertex liner[] =
	{
		sf::Vertex(sf::Vector2f(Range.GetBR().GetX(), Range.GetBR().GetY())),
		sf::Vertex(sf::Vector2f(Range.GetBR().GetX(), Range.GetTL().GetY()))
	};
	sf::Vertex lines[] =
	{
		sf::Vertex(sf::Vector2f(Range.GetTL().GetX(), Range.GetTL().GetY())),
		sf::Vertex(sf::Vector2f(Range.GetBR().GetX(), Range.GetTL().GetY()))
	};

	window_.draw(line, 2, sf::Lines);
	window_.draw(linee, 2, sf::Lines);
	window_.draw(liner, 2, sf::Lines);
	window_.draw(lines, 2, sf::Lines);
}

void QuadTree::CleanTree()
{
	if (!(node[0] == nullptr))
	{
		node[0]->CleanTree();
		node[1]->CleanTree();
		node[2]->CleanTree();
		node[3]->CleanTree();
	}

	parent = nullptr;
	delete parent;
	for (short i = 0; i < 4; i++)
	{
		delete node[i];
		node[i] = nullptr;
	}
	itemlist.clear();
	itemlist.shrink_to_fit();
}