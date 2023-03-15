#pragma once
#include <vector>
#include "agent.h"
#include "ThreadSafeQueue.h"
#include <queue>

class agent;

class agent_parameters
{
	unsigned int id_;
	std::vector<agent*> neighbours_;
	int max_neighbour_capacity_;
	bool changable_;
public:
	ThreadSafeQueue<message::message> message_queue_;

	agent_parameters()
	{
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = -1;
	}

	agent_parameters(int id)
	{
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = id;
	}

	agent_parameters(agent_parameters &other_parameters)
	{
		changable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
	}

	agent_parameters(agent_parameters* other_parameters)
	{
		changable_ = other_parameters->changable_;
		max_neighbour_capacity_ = other_parameters->max_neighbour_capacity_;
		id_ = other_parameters->id_;
	}

	//agent_parameters(unsigned int id, int x_location, int y_location) : id(id), x_location(x_location), y_location(y_location){}

	agent_parameters& operator=(agent_parameters& other_parameters)
	{
		changable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
		return *this;
	}

	bool add_neighbour(agent *neigh)
	{
		if (!changable_)
			throw std::runtime_error("agent not mutable");

		if (neighbours_.size() < max_neighbour_capacity_) {
			neighbours_.push_back(neigh);
			return true;
		}
		return false;
	}

	bool remove_neighbour(agent* neigh)
	{
		if (!changable_)
			throw std::runtime_error("agent not mutable");

		for (std::vector<agent*>::iterator iter = neighbours_.begin(); iter != neighbours_.end(); iter++)
		{
			if (*iter == neigh) {
				neighbours_.erase(iter);
				return true;
			}
		}
		return false;
		
	}

	void open_for_change()
	{
		changable_ = true;
	}

	void close_for_change()
	{
		changable_ = false;
	}

	unsigned int get_id()
	{
		return id_;
	}
};