#pragma once
#pragma once
#include "Cooldown.h"
#include "Movable.h"
#include "Graphics.h"
#include "Object.h"

enum stype { melee = 10, ranged };

class Skill : public Movable, public std::enable_shared_from_this<Skill>
{
private:
	std::shared_ptr<Object> owner;
	Cooldown cd, timetolive, animantioncooldown;
	std::shared_ptr<Graphics> mdisp;
	short skilltype;
	short direction;

	Skill() {
		skilltype = 0; direction = left;
	}

	////////////////////////////////////////////////////////////////////////////////////////
	//Movement managment			
	//
	//\brief   moves the object
	//
	//\param spdx   movement value - pixels in the x axis
	//\param spdy   movement value - pixels in the y axis
	////////////////////////////////////////////////////////////////////////////////////////
	void Move(double xspd, double yspd);

	void UpdatePRTO();

	void UpdateRanged();

public:

	Skill(Point Point_of_creation, double cooldown, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt, short direction, std::shared_ptr<Object> o = nullptr);

	void isTimeToDie();
	////////////////////////////////////////////////////////////////////////////////////////
	//collision resolution		
	//
	//\brief   resolves intersection with different object types								
	////////////////////////////////////////////////////////////////////////////////////////
	void intersection(Object* obj);

	////////////////////////////////////////////////////////////////////////////////////////
	//Graphical draw			
	//
	//\brief   Draws the object	to the window						
	////////////////////////////////////////////////////////////////////////////////////////
	void draw();

	////////////////////////////////////////////////////////////////////////////////////////
	//accessor			
	//
	//\brief   returns the object type											
	////////////////////////////////////////////////////////////////////////////////////////
	virtual short reType();

	////////////////////////////////////////////////////////////////////////////////////////
	//Graphics updater		
	//
	//\brief   updates the graphical position of the object and any other graphical changes									
	////////////////////////////////////////////////////////////////////////////////////////
	void refreshgraphics(sf::Vector2f pos);


	void UpdateMO();

	std::shared_ptr<Object> returnowner();

	void action();

	~Skill();
};