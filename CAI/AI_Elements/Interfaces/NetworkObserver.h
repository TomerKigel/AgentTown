#pragma once
#include "Observer.h"
#include <memory>
#include "../agent.h"
class NetworkObserver : public Observer
{
	virtual void agent_added(std::shared_ptr<agent> added_agent);
	virtual void agent_removed(std::shared_ptr<agent> added_agent);
};