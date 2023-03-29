#pragma once
#include <vector>
#include "agent.h"
#include "../Message_System/QueueManager.h"
#include "../Message_System/MessageParser.h"
#include <queue>

class agent;

class agent_parameters
{
	unsigned int id_,connection_id_;
	std::vector<int> neighbours_;
	int max_neighbour_capacity_;
	bool changable_;
public:
	QueueManager<message::ParsedMessage> message_queue_;

	agent_parameters()
	{
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = -1;
		connection_id_ = -1;
	}

	agent_parameters(int id)
	{
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = id;
		connection_id_ = -1;
	}

	agent_parameters(int id,int connection)
	{
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = id;
		connection_id_ = connection;
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


	agent_parameters& operator=(agent_parameters& other_parameters)
	{
		changable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
		return *this;
	}

	bool add_neighbour(int id)
	{
		if (!changable_)
			throw std::runtime_error("agent not mutable");

		if (neighbours_.size() < max_neighbour_capacity_) {
			neighbours_.push_back(id);
			return true;
		}
		return false;
	}

	bool remove_neighbour(int id)
	{
		if (!changable_)
			throw std::runtime_error("agent not mutable");

		std::erase(neighbours_,id);
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

	unsigned int get_connection_id()
	{
		return connection_id_;
	}
};