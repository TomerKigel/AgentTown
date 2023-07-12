#pragma once
#include <vector>
#include "Agent.h"
#include "../Message_System/Queue_Manager.h"
#include "../Message_System/Message_Parser.h"
//#include "spdlog/spdlog.h"

class Agent;

class Agent_Parameters
{
	double location_x_, location_y_;
	unsigned int id_,connection_id_;
	std::vector<int> neighbors_;
	int max_neighbour_capacity_;
	bool changeable_;
public:
	Queue_Manager<message::Parsed_Message> message_queue_;

	Agent_Parameters()
	{
		location_x_ = location_y_ = 0;
		max_neighbour_capacity_ = 100;
		changeable_ = true;
		id_ = -1;
		connection_id_ = -1;
		//spdlog::info("agent created with invalid id and connection id");
	}

	Agent_Parameters(int id, double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
		changeable_ = true;
		id_ = id;
		connection_id_ = -1;
		//spdlog::warn("agent created with invalid connection id");
	}

	Agent_Parameters(int id, int connection, double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
		changeable_ = true;
		id_ = id;
		connection_id_ = connection;
	}


	Agent_Parameters(Agent_Parameters &other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
		changeable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
		connection_id_ = other_parameters.connection_id_;
	}

	Agent_Parameters(Agent_Parameters* other_parameters)
	{
		location_x_ = other_parameters->location_x_;
		location_y_ = other_parameters->location_y_;
		changeable_ = other_parameters->changeable_;
		max_neighbour_capacity_ = other_parameters->max_neighbour_capacity_;
		id_ = other_parameters->id_;
		connection_id_ = other_parameters->connection_id_;
	}


	Agent_Parameters& operator=(Agent_Parameters& other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
		changeable_ = true;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		id_ = other_parameters.id_;
		return *this;
	}

	bool add_neighbour(int id)
	{
		if (!changeable_)
			throw std::runtime_error("agent not mutable");

		if (neighbors_.size() < max_neighbour_capacity_) {
			neighbors_.push_back(id);
			return true;
		}
		return false;
	}

	bool remove_neighbour(int id) 
	{
		if (!changeable_)
			throw std::runtime_error("agent not mutable");

		std::erase(neighbors_,id);
		return false;
	}

	void open_for_change() noexcept
	{
		changeable_ = true;
	}

	void close_for_change() noexcept
	{
		changeable_ = false;
	}

	unsigned int get_id() const
	{
		if (id_ == -1)
			throw std::exception("agent has no valid id");
		return id_;
	}

	unsigned int get_connection_id() const
	{
		if (id_ == -1)
			throw std::exception("agent has no valid connection_id");
		return connection_id_;
	}

	std::pair<double, double> getLocation() const noexcept
	{
		return std::make_pair(location_x_, location_y_);
	}

	void setLocation(double x, double y) noexcept
	{
		location_x_ = x;
		location_y_ = y;
	}
};