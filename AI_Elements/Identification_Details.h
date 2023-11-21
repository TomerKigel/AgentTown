#pragma once

#include <iostream>

class Identification_Details
{
public:
	Identification_Details()
	{
		agent_id_ = 0;
		connection_id_ = 0;
	}
	Identification_Details(unsigned int agent_id, unsigned int connection_id)
	{
		this->agent_id_ = agent_id;
		this->connection_id_ = connection_id;
	}

	void set_id(int id) noexcept
	{
		if (id > 0)
			agent_id_ = id;
		else
		{
			std::cerr << "set_id: attempt to set id to a negative, operation canceled";
		}
	}
	void set_connection_id(int id) noexcept
	{
		if (id > 0)
			connection_id_ = id;
		else
		{
			std::cerr << "set_id: attempt to set connection id to a negative, operation canceled";
		}
	}

	//accessors
	unsigned int get_id() const
	{
		if (agent_id_ == -1)
			throw std::runtime_error("agent has no valid id");
		return agent_id_;
	}

	unsigned int get_connection_id() const
	{
		if (connection_id_ == -1)
			throw std::runtime_error("agent has no valid connection_id");
		return connection_id_;
	}
private:
	unsigned int agent_id_, connection_id_;
};