#include "Cooldown.h"

Cooldown::Cooldown(double seconds)
{
	clk.restart();
	clkMaxLim = seconds;
}
void Cooldown::SetTimerMaxAsSeconds(double seconds)
{
	clkMaxLim = seconds;
}
void Cooldown::IncTimerBySeconds(double seconds)
{
	clkMaxLim += seconds;
}
void Cooldown::DecTimerBySeconds(double seconds)
{
	clkMaxLim -= seconds;
}
bool Cooldown::IsTimeUp() const
{
	if (clk.getElapsedTime().asSeconds() > clkMaxLim)
		return true;
	else
		return false;
}
const void Cooldown::resetTimer()
{
	clk.restart();
}

const double Cooldown::reTime()
{
	return clk.getElapsedTime().asSeconds();
}

const double Cooldown::reMaxTime()
{
	return clkMaxLim;
}

Cooldown::~Cooldown()
{
	;
}