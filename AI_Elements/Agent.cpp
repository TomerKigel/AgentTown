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

#include "Agent.h"

void Agent::push_message(message::Parsed_Message& msg)
{
	processor_->push_message(msg);
}

Agent::Agent()
{
	processor_ = std::make_unique<Message_Processor>(&parameters_, &observers_);
	parameters_.revive();
	info_.set_connection_id(0);
	info_.set_id(0);
	processor_->run();
}

Agent::Agent(int id, int connection_id)
{
	processor_ = std::make_unique<Message_Processor>(&parameters_, &observers_);
	parameters_.revive();
	if (id < 0)
		throw std::runtime_error("Negative id in agent creation");
	if (connection_id < 0)
		throw std::runtime_error("Negative connection_id in agent creation");
	info_.set_connection_id(connection_id);
	info_.set_id(id);
	processor_->run();
}

Agent::Agent(Agent& other_agent)
{
	processor_ = std::make_unique<Message_Processor>(&parameters_, &observers_);
	Agent_Parameters a(other_agent.parameters_);
	parameters_ = a;
	processor_->run();
}

Agent& Agent::operator=(Agent& other)
{
	parameters_.revive();
	Agent_Parameters a(other.parameters_);
	parameters_ = a;
	processor_ = std::make_unique<Message_Processor>(&parameters_, &observers_);
	return *this;
}

Agent::~Agent()
{
	this->parameters_.kill();
}

bool Agent::add_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	try {
		return parameters_.add_neighbour(id);
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		return false;
	}
}

bool Agent::remove_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	try {
		return parameters_.remove_neighbour(id);
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		return false;
	}
}

void Agent::set_connection_id(int id)
{
	info_.set_connection_id(id);
}

void Agent::set_id(int id)
{
	info_.set_id(id);
}

unsigned int Agent::get_connection_id()
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	try {
		return info_.get_connection_id();
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		throw e;
	}
}

unsigned int Agent::get_agent_id()
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	try {
		return info_.get_id();
	}
	catch (std::exception e)
	{
		std::cerr << e.what();
		throw e;
	}
}


void Agent::pause()
{

}

void Agent::subscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
{
	std::lock_guard<std::mutex>lock(observers_mutex_);
	observers_.push_back(obs);
}

void Agent::unsubscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
{
	std::lock_guard<std::mutex>lock(observers_mutex_);
	std::remove_if(observers_.begin(), observers_.end(), [obs](const std::weak_ptr<Interface_Graphics_Observer>& a) {return a.lock() == obs; });
}


std::pair<double, double> Agent::get_position()
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	return parameters_.getLocation();
}

void Agent::update_position(std::pair<double, double> x_y)
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	parameters_.setLocation(x_y.first, x_y.second);
	std::lock_guard<std::mutex>olock(observers_mutex_);
	for (std::weak_ptr<Interface_Graphics_Observer> obs : observers_)
		obs.lock()->update_position(x_y.first, x_y.second);
}
