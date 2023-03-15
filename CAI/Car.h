#pragma once
#include "Movable.h"
#include "agent.h"
#include "Graphics.h"
#include "MessageParser.h"
#include "message.h"
#include <optional>


class Car : public agent, public std::enable_shared_from_this<Car>
{
private:
	std::shared_ptr<Graphics> mdisp;
	Point *focus;
	double ohight;
	Cooldown attTimer,cd;
public:
	Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id);
	void Controls();
	void intersection(Object* obj);
	short reType();
	void Move(double xspd, double yspd);
	void draw();
	void action();

	void process_message(message::message& msg);
	~Car() {}
};