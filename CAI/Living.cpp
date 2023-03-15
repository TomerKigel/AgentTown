#include "Living.h"

Living::Living(double hp, double ad)
{
	HealthPoints = hp;
	AttackDamage = ad;
	Stamina = maxStamina = 100;
	Shield = 0;
}

void Living::IncHealth(double value)
{
	HealthPoints += value;
	if (HealthPoints > maxHealthPoints)
		HealthPoints = maxHealthPoints;
}

void Living::DecHealth(double value)
{
	HealthPoints -= value;

	if (HealthPoints < 0)
		HealthPoints = 0;
}

void Living::IncStamina(double value)
{
	Stamina += value;
	if (Stamina > maxStamina)
		Stamina = maxStamina;
}

void Living::DecStamina(double value)
{
	Stamina -= value;

	if (Stamina < 0)
		Stamina = 0;
}

bool Living::SetHealth(double value)
{
	if (value >= 0)
		maxHealthPoints = HealthPoints = value;
	else
		return false;
	return true;
}

void Living::SetAttack(double value)
{
	AttackDamage = value;
}

double Living::getAttack()
{
	return AttackDamage;
}

void Living::setLevelUps()
{

}

void Living::LevelUp()
{

}

bool Living::isLiving()
{
	return (bool)HealthPoints;
}

double Living::reStamina()
{
	return Stamina;
}

Living::~Living()
{

}