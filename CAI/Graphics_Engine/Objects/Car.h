#pragma once

#include "../Cooldown.h"
#include "../Space/Point.h"
#include "../../AI_Elements/agent.h"
#include "../../Graphics_Engine/Graphics/Graphics.h"
#include "SFML\Graphics.hpp"

class Car : public agent, public std::enable_shared_from_this<Car>
{
private:
	std::shared_ptr<Graphics> mdisp;
	Point *focus;
	double ohight;
	Cooldown attTimer,cd;
public:
	Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id,int connection_id);
	void Controls();
	void intersection(Object* obj);
	short reType();
	void Move(double xspd, double yspd);
	void draw();
	void action();
	void process_message(message::ParsedMessage& msg);
	~Car() {}
};