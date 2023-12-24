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