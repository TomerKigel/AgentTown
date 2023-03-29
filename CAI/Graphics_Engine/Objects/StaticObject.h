#pragma once

#include <SFML/Graphics.hpp>
#include "../Graphics/Graphics.h"
#include "../Graphics/Textures.h"
#include "../Objects/Object.h"

class StaticObject : public Object, public std::enable_shared_from_this<StaticObject>
{
private:
	std::shared_ptr<Graphics> disp;
	sf::Texture tx;
	StaticObject();
public:
	////////////////////////////////////////////////////////////////////////////////////////
	//Constructor
	//
	//\param range     AABB of the object
	//\param window_    window_ handle
	//\param txt       texture for displaying the object
	////////////////////////////////////////////////////////////////////////////////////////
	StaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt);

	virtual short reType();

	void draw();

	virtual void intersection(Object* obj);

	void refreshgraphics(sf::Vector2f pos);

	void action() {};

	~StaticObject() {}
};