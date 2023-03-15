#pragma once
#include "interface_calculatable.h"
class distanceCalculatable : public interface_calculatable
{
	double calculate()
	{
		return 1.0;
	}
};