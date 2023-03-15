#pragma once
#include "Monster.h"
#include "Skill.h"

class Yeti : public Monster
{
private:
	Cooldown attTimer;
public:
	Yeti(double tspd, AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt);
	void Controls();
	void intersection(Object* obj);
	short reMType();
	void Attack();
	~Yeti() {}
};