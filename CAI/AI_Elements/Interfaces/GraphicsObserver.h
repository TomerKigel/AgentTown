#pragma once
#include <string>
class GraphicsObserver
{
public:
	virtual void update_position(double x,double y) = 0;
	virtual void kill() = 0;
	virtual void show(bool state) = 0;
	virtual void update_display_information(std::string) = 0;
};