#include "Car.h"
#include "../Factory.h"

Car::Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id)
{
	set_id(id);
	setAABB(range);
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetLen(), range.GetWid());
		mdisp = std::make_shared<Graphics>(cor, siz, window_);
	}
	else
	{
		mdisp = std::make_shared<Graphics>(cor, txt, window_, getAABB());
	}
	PhysicsStats pps;
	pps.topspeed = tspd;
	pps.accx = 0;
	pps.accy = 0;
	pps.topacc = 100;
	pps.xspeed = 0;
	pps.yspeed = 0;
	ph.setObjectsParameters(pps);
	refreshLastSpace();
	focus = nullptr;
	cd.SetTimerMaxAsSeconds(0.1);
}

void Car::Controls()
{
	if (cd.IsTimeUp()) {
		if (focus == nullptr) {
			ph;
		}
		else
		{
			ph;
		}
		cd.resetTimer();
	}
}

void Car::intersection(Object* obj)
{
	switch (obj->reType())
	{
	
	}
}

void Car::Move(double xspd, double yspd)
{
	std::unique_lock<std::mutex> lock(car_mutex);
	getAABB()->SetTL(getAABB()->GetTL().GetX() + xspd, getAABB()->GetTL().GetY() + yspd);
	getAABB()->SetBR(getAABB()->GetBR().GetX() + xspd, getAABB()->GetBR().GetY() + yspd);
}


void Car::draw()
{
	std::unique_lock<std::mutex> lock(car_mutex);
	refreshLastSpace();
	sf::Vector2f cor(space.GetTL().GetX(), space.GetTL().GetY());
	mdisp->refreshPosition(cor);
	mdisp->Draw();
}

void Car::action()
{
	Controls();
	PhysicsInit();
}

void Car::update_position(double x, double y)
{
	std::unique_lock<std::mutex> lock(car_mutex);
	getAABB()->SetTL(x , y);
	getAABB()->SetBR(getAABB()->GetLen() + x, getAABB()->GetWid() + y);
}

void Car::kill()
{
	std::unique_lock<std::mutex> lock(car_mutex);
	destruct = true;
}

void Car::show(bool state)
{

}

void Car::update_display_information(std::string)
{

}


short Car::reType()
{
	return cartype;
}

//
//void Car::process_message(message::ParsedMessage& msg)
//{
//	if (msg.x_position && msg.y_position)
//	{
//		getAABB()->SetTL(msg.x_position.value(), msg.y_position.value());
//		getAABB()->SetBR(msg.x_position.value()+ getAABB()->GetLen(), msg.y_position.value() + getAABB()->GetWid());
//	}
//	if (msg.type == "disconnect")
//		destroy();
//}
