#include "Car.h"
#include "Factory.h"

Car::Car(double tspd, AABB range, std::shared_ptr<sf::RenderWindow> window_, std::shared_ptr<sf::Texture> txt,int id) : agent(id)
{
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
	getAABB()->SetTL(getAABB()->GetTL().GetX() + xspd, getAABB()->GetTL().GetY() + yspd);
	getAABB()->SetBR(getAABB()->GetBR().GetX() + xspd, getAABB()->GetBR().GetY() + yspd);
}


void Car::draw()
{
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


short Car::reType()
{
	return cartype;
}

void Car::process_message(message::message& msg)
{
	auto pmsg = message::parse_message(msg);
	if (pmsg.x_position && pmsg.y_position)
	{
		getAABB()->SetTL(pmsg.x_position.value(), pmsg.y_position.value());
		getAABB()->SetBR(pmsg.x_position.value()+ getAABB()->GetLen(), pmsg.y_position.value() + getAABB()->GetWid());
	}
}