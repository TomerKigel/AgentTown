#pragma once
#include <string>
#include "Interface_Observer.h"
class Interface_Graphics_Observer : public Interface_Observer
{
public:
	virtual void update_position(double x,double y) = 0;
	virtual void kill() = 0;
	virtual void show(bool state) = 0;
	virtual void update_display_information(std::string) = 0;
};