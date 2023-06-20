#pragma once

#include "../Cooldown.h"
#include "../Space/Point.h"
#include "../../AI_Elements/agent.h"
#include "../../Graphics_Engine/Graphics/Graphics.h"
#include "SFML\Graphics.hpp"
#include "../../AI_Elements/Interfaces/GraphicsObserver.h"
class Car : public std::enable_shared_from_this<Car> , public Movable, public GraphicsObserver
{
private:
	std::shared_ptr<Graphics> mdisp;
	Point *focus;
	double ohight;
	Cooldown attTimer,cd;
	std::mutex car_mutex;
public:
	Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id,int connection_id);
	virtual void destroy() {destruct = true;}
	void Controls();
	void intersection(Object* obj);
	short reType();
	void Move(double xspd, double yspd);
	void draw();
	void action();
	//void process_message(message::ParsedMessage& msg);

	virtual void update_position(double x, double y);
	virtual void kill();
	virtual void show(bool state);
	virtual void update_display_information(std::string);

	~Car() {}
};