#pragma once
#include <vector>
#include "Agent.h"
#include "../Message_System/Queue_Manager.h"
#include "../Message_System/Message_Parser.h"

class Agent;

class Agent_Parameters
{
	double location_x_, location_y_;
	std::vector<int> neighbors_;
	int max_neighbour_capacity_;
	bool changeable_ = true;
	bool alive_ = true;
public:
	Agent_Parameters(double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
	}

	Agent_Parameters(Agent_Parameters &other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
	}

	Agent_Parameters(Agent_Parameters* other_parameters)
	{
		location_x_ = other_parameters->location_x_;
		location_y_ = other_parameters->location_y_;
		changeable_ = other_parameters->changeable_;
		max_neighbour_capacity_ = other_parameters->max_neighbour_capacity_;
	}


	Agent_Parameters& operator=(Agent_Parameters& other_parameters)
	{
		location_x_ = other_parameters.location_x_;
		location_y_ = other_parameters.location_y_;
		max_neighbour_capacity_ = other_parameters.max_neighbour_capacity_;
		return *this;
	}

	bool is_alive()
	{
		return alive_;
	}

	void kill()
	{
		alive_ = false;
	}

	void revive()
	{
		alive_ = true;
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