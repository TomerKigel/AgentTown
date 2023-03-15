#pragma once
#include <SFML/Graphics.hpp>

class Cooldown
{
private:
	sf::Clock clk;
	double clkMaxLim;
public:
	Cooldown() { clkMaxLim = 1; }
	
	Cooldown(double seconds);
	
	void SetTimerMaxAsSeconds(double seconds);
	
	void IncTimerBySeconds(double seconds);
	
	void DecTimerBySeconds(double seconds);
	
	bool IsTimeUp() const;
	
	const void resetTimer();

	const double reTime();

	const double reMaxTime();

	~Cooldown();
};