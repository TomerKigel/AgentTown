#include "StaticObject.h"

StaticObject::StaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt)
{
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetLen(), range.GetWid());
		disp = std::make_shared<Graphics>(cor, siz, window_);
	}
	else
	{
		disp = std::make_shared <Graphics>(cor, txt, window_);
	}
	space = range;
}

void StaticObject::draw()
{
	disp->Draw();
}

void StaticObject::intersection(Object* obj)
{
	switch (obj->reType())
	{
	case cartype:
		break;
	}
}

void StaticObject::refreshgraphics(sf::Vector2f pos)
{
	disp->refreshPosition(pos);
}

short StaticObject::reType()
{
	return sttc;
}