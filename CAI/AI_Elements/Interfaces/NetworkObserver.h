#pragma once
#include "Observer.h"
#include <memory>
#include "../agent.h"
class NetworkObserver : public Observer
{
public:
	virtual void agent_added(std::shared_ptr<agent> added_agent) = 0;
	virtual void agent_removed(std::shared_ptr<agent> added_agent) = 0;
};