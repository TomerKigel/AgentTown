#pragma once
#include "Component.h"

enum class system_state { RUNNING, PAUSED, TERMINATED };

template <class T>
class System : public Component
{
public:
	virtual void provide_message(T& msg) = 0;

	system_state state()
	{
		return system_state_;
	}

protected:
	system_state system_state_;
};