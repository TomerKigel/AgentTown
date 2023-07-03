#pragma once
#include <vector>
#include "Agent.h"
#include "../Message_System/Queue_Manager.h"
#include "../Message_System/Message_Parser.h"

class Agent;

class Agent_Parameters
{
	double location_x_, location_y_;
	unsigned int id_,connection_id_;
	std::vector<int> neighbours_;
	int max_neighbour_capacity_;
	bool changable_;
public:
	Queue_Manager<message::ParsedMessage> message_queue_;

	Agent_Parameters()
	{
		location_x_ = location_y_ = 0;
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = -1;
		connection_id_ = -1;
	}

	Agent_Parameters(int id, double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = id;
		connection_id_ = -1;
	}

	Agent_Parameters(int id, int connection, double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
		changable_ = true;
		id_ = id;
		connection_id_ = connection;
	}


	Agent_Parameters(Agent_Parameters &other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
		changable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
		connection_id_ = other_parameters.connection_id_;
	}

	Agent_Parameters(Agent_Parameters* other_parameters)
	{
		location_x_ = other_parameters->location_x_;
		location_y_ = other_parameters->location_y_;
		changable_ = other_parameters->changable_;
		max_neighbour_capacity_ = other_parameters->max_neighbour_capacity_;
		id_ = other_parameters->id_;
		connection_id_ = other_parameters->connection_id_;
	}


	Agent_Parameters& operator=(Agent_Parameters& other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
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

	unsigned int get_id() const
	{
		return id_;
	}

	unsigned int get_connection_id() const
	{
		return connection_id_;
	}

	std::pair<double, double> getLocation() const
	{
		return std::make_pair(location_x_, location_y_);
	}

	void setLocation(double x, double y)
	{
		location_x_ = x;
		location_y_ = y;
	}
};