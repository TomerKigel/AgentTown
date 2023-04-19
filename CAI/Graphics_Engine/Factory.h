#pragma once

#include <string>
#include "../Graphics_Engine/Objects/StaticObject.h"
#include "../Graphics_Engine/Space/AABB.h"
#include "../Graphics_Engine/Sound/Sound.h"
#include "../Graphics_Engine/Graphics/Textures.h"
#include "../Graphics_Engine/Objects/Car.h"
#include "interfaces/Interactable.h"

////////////////////////////////////////////////////////////////////////////////////////
//Structeture of monster parameters	
//
//\brief   Struct that hold data about the object that is about to be created
////////////////////////////////////////////////////////////////////////////////////////
struct CarParameters
{
	AABB range;
	std::shared_ptr<sf::RenderWindow> window_;
	std::shared_ptr<sf::Texture> texture;
	double speed = 1;
	int id;
	int connection_id;
};

////////////////////////////////////////////////////////////////////////////////////////
//Structeture of Static Objects parameters	
//
//\brief   Struct that hold data about the object that is about to be created
////////////////////////////////////////////////////////////////////////////////////////
struct StaticParameters
{
	AABB range;
	std::shared_ptr<sf::RenderWindow> window_;
	std::shared_ptr<sf::Texture> texture;
};



class Factory
{
private:
	static std::unique_ptr<std::vector<std::shared_ptr<Object>>> Object_List;
	static CarParameters Car_Parameters;
	static StaticParameters StaticObject_Parameters;
public:
	static std::unique_ptr<std::vector<std::shared_ptr<Object>>> extract_object_list();
	static void destoryList();
	static void destoryObject(int i);
	////////////////////////////////////////////////////////////////////////////////////////
	//Car Creater 			
	//
	//\brief   Creates an objects using parameters defined in Car_Parameters
	////////////////////////////////////////////////////////////////////////////////////////
	static std::shared_ptr<Car> CreateCar();


	////////////////////////////////////////////////////////////////////////////////////////
	//Static object Creater 			
	//
	//\brief   Creates an objects using parameters defined in StaticObject_Parameters
	////////////////////////////////////////////////////////////////////////////////////////
	static std::shared_ptr<StaticObject> CreateStaticObject();

	////////////////////////////////////////////////////////////////////////////////////////
	//Sound singelton Creater 			
	////////////////////////////////////////////////////////////////////////////////////////
	static std::shared_ptr<Sound> CreateSound();

	////////////////////////////////////////////////////////////////////////////////////////
	//Texture singelton Creater 			
	////////////////////////////////////////////////////////////////////////////////////////
	static std::shared_ptr<Textures> CreatGameAssets();

	////////////////////////////////////////////////////////////////////////////////////////
	//Set up parameters in param types			
	//
	//\brief   sets up all variables inside 'Parameters' types
	//
	//\param tlx,tly,brx,bry,TL,BR,range   position of the rectangle to be created by X and Y values or two points or an aabb range	
	////////////////////////////////////////////////////////////////////////////////////////
	union SetUpCar
	{
		static void new_SetUpCar(double tlx = 0, double tly = 0, double brx = 0, double bry = 0, double spd = 5, std::shared_ptr<sf::RenderWindow> window_ = nullptr,int id = -1, int connection = 0);
		static void new_SetUpCar(Point Tl, Point Br, double spd = 5, std::shared_ptr<sf::RenderWindow> window_ = nullptr, int id = -1, int connection = 0);
		static void new_SetUpCar(AABB range, double spd = 5, std::shared_ptr<sf::RenderWindow> window_ = nullptr, int id = -1, int connection = 0);
	};
	union SetUpStatic
	{
		static void SetUpStaticObject(double tlx = 0, double tly = 0, double brx = 0, double bry = 0, std::shared_ptr<sf::RenderWindow> window_ = nullptr, std::string filename = "");
		static void SetUpStaticObject(Point Tl, Point Br, std::shared_ptr<sf::RenderWindow> window_ = nullptr, std::string filename = "");
		static void SetUpStaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window_ = nullptr, std::string filename = "");
	};
};