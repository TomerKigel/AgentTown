#pragma once

#include "../Cooldown.h"
#include "../Space/Point.h"
#include "../../AI_Elements/Agent.h"
#include "../../Graphics_Engine/Graphics/Graphics.h"
#include "SFML\Graphics.hpp"
#include "../../AI_Elements/Interfaces/Interface_Graphics_Observer.h"
#include "Movable.h"
class Car : public std::enable_shared_from_this<Car> , public Movable, public Interface_Graphics_Observer
{
private:
	std::shared_ptr<Graphics> mdisp_;
	Point *focus_;
	double ohight_;
	Cooldown attTimer_,cd_;
	std::mutex car_mutex_;
public:
	Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id);
	virtual void destroy() {destruct = true;}
	void controls();
	void intersection(Object* obj);
	short reType();
	void move(double xspd, double yspd);
	void draw();
	void action();
	//void process_message(message::ParsedMessage& msg);

	virtual void update_position(double x, double y);
	virtual void kill();
	virtual void show(bool state);
	virtual void update_display_information(std::string);

	~Car() {}
};