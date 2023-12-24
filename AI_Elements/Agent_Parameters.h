/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/
#pragma once
#include <vector>
#include <algorithm>

#include "Agent.h"
#include "Queue_Manager.h"
#include "Message_Parser.h"


class Agent;

class Agent_Parameters
{
public:
	Agent_Parameters(double x = 0, double y = 0)
	{
		location_x_ = x;
		location_y_ = y;
		max_neighbour_capacity_ = 100;
	}

	Agent_Parameters(Agent_Parameters& other_parameters)
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

		std::erase(neighbors_, id);
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
private:
	double location_x_, location_y_;
	std::vector<int> neighbors_;
	int max_neighbour_capacity_;
	bool changeable_ = true;
	bool alive_ = true;
};