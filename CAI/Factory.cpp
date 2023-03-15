#pragma once
#include "Factory.h"
#include <SFML\Graphics.hpp>

CarParameters Factory::Car_Parameters;
StaticParameters Factory::StaticObject_Parameters;


std::unique_ptr<std::vector<std::shared_ptr<Object>>> Factory::Object_List = std::make_unique<std::vector<std::shared_ptr<Object>>>();
static std::shared_ptr<Sound> tpl = nullptr;
static std::shared_ptr<Textures> GameAssets = nullptr;

std::unique_ptr<std::vector<std::shared_ptr<Object>>> Factory::extract_object_list()
{
	std::unique_ptr<std::vector<std::shared_ptr<Object>>> temp_ptr = std::move(Object_List);
	Object_List = std::make_unique<std::vector<std::shared_ptr<Object>>>();
	return std::move(temp_ptr);
}

void Factory::destoryList()
{
	Object_List->clear();
}

void Factory::destoryObject(int i)
{
	Object_List->erase(Object_List->begin() + i);
	Object_List->shrink_to_fit();
}

std::shared_ptr<Car> Factory::CreateCar()
{
	std::shared_ptr<sf::Texture> text = std::make_shared<sf::Texture>();
	text->loadFromFile("car.png");
	std::shared_ptr<Car> tm = std::make_shared<Car>(Car_Parameters.speed,Car_Parameters.range, Car_Parameters.window_, text, Car_Parameters.id);
	Object_List->push_back(tm);
	return tm;
}

std::shared_ptr<StaticObject> Factory::CreateStaticObject()
{
	std::shared_ptr<StaticObject> ts = std::make_shared<StaticObject>(StaticObject_Parameters.range, StaticObject_Parameters.window_, StaticObject_Parameters.texture);
	Object_List->push_back(ts);
	return ts;
}


std::shared_ptr<Sound> Factory::CreateSound()
{
	if (tpl == nullptr) {
		tpl = std::make_shared<Sound>();
	}

	return tpl;
}

std::shared_ptr<Textures> Factory::CreatGameAssets()
{
	if (GameAssets == nullptr) {
		GameAssets = std::make_shared<Textures>();
	}

	return GameAssets;
}


void Factory::SetUpCar::new_SetUpCar(double tlx, double tly, double brx, double bry, double spd, std::shared_ptr<sf::RenderWindow> window_, int id)
{
	Car_Parameters.range(tlx, tly, brx, bry);
	Car_Parameters.window_ = window_;
	Car_Parameters.speed = spd;
	Car_Parameters.id = id;
}

void Factory::SetUpCar::new_SetUpCar(Point Tl, Point Br, double spd, std::shared_ptr<sf::RenderWindow> window_, int id)
{
	Car_Parameters.range(Tl, Br);
	Car_Parameters.window_ = window_;
	Car_Parameters.speed = spd;
	Car_Parameters.id = id;
}

void Factory::SetUpCar::new_SetUpCar(AABB range, double spd, std::shared_ptr<sf::RenderWindow> window_, int id)
{
	Car_Parameters.range = range;
	Car_Parameters.window_ = window_;
	Car_Parameters.speed = spd;
	Car_Parameters.id = id;
}


void Factory::SetUpStatic::SetUpStaticObject(double tlx, double tly, double brx, double bry, std::shared_ptr<sf::RenderWindow> window_, std::string filename)
{
	StaticObject_Parameters.range(tlx, tly, brx, bry);
	StaticObject_Parameters.window_ = window_;
	if (filename != "")
	{
		StaticObject_Parameters.texture = std::make_shared<sf::Texture>(*GameAssets->getTexture(filename));
	}
}

void Factory::SetUpStatic::SetUpStaticObject(Point Tl, Point Br, std::shared_ptr<sf::RenderWindow> window_, std::string filename)
{
	StaticObject_Parameters.range(Tl, Br);
	StaticObject_Parameters.window_ = window_;
	if (filename != "")
	{
		StaticObject_Parameters.texture = std::make_shared<sf::Texture>(*GameAssets->getTexture(filename));
	}
}

void Factory::SetUpStatic::SetUpStaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window_, std::string filename)
{
	StaticObject_Parameters.range = range;
	StaticObject_Parameters.window_ = window_;
	if (filename != "")
	{
		StaticObject_Parameters.texture = std::make_shared<sf::Texture>(*GameAssets->getTexture(filename));
	}
}
