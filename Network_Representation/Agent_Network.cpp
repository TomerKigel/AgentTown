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
#include "Agent_Network.h"


Agent_Network::Agent_Network(std::string name_)
{
	this->name_ = name_;
	alive_ = true;
	_system_state_ = system_state::RUNNING;
}
void Agent_Network::add_node(int id, int connection)
{
	std::scoped_lock lock(nodes_mutex_);
	_nodes_.insert(std::make_pair(id, std::make_shared<Agent>(id, connection)));
	for (auto iter = _network_observers_.begin(); iter != _network_observers_.end(); iter++)
	{
		(*iter)->agent_added(_nodes_.at(id));
	}
}

void Agent_Network::remove_node(int id)
{
	std::scoped_lock lock(nodes_mutex_);
	if (_nodes_.count(id) != 0) {
		for (auto iter = _network_observers_.begin(); iter != _network_observers_.end(); iter++)
		{
			(*iter)->agent_removed(_nodes_.at(id));
		}
		std::erase_if(_nodes_, [id](std::pair<int, std::shared_ptr<Agent>> a) {return a.first == id; });
	}
}

void Agent_Network::add_neighbour_to_agent(int agent_id, int neighbour_id)
{
	std::scoped_lock lock(nodes_mutex_);
	auto found_agent = std::find_if(_nodes_.begin(), _nodes_.end(), [agent_id](std::pair<int, std::shared_ptr<Agent>> a) {return a.first == agent_id; });
	if ((*found_agent).second->get_agent_id() == agent_id)
		(*found_agent).second->add_neighbour(neighbour_id);
}

void Agent_Network::remove_neighbour_to_agent(int agent_id, int neighbour_id)
{
	std::scoped_lock lock(nodes_mutex_);
	auto found_agent = std::find_if(_nodes_.begin(), _nodes_.end(), [agent_id](std::pair<int, std::shared_ptr<Agent>> a) {return a.first == agent_id; });
	if ((*found_agent).second->get_agent_id() == agent_id)
		(*found_agent).second->remove_neighbour(neighbour_id);
}

void Agent_Network::subscribe_to_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer)
{
	std::scoped_lock lock(nodes_mutex_);
	_nodes_.at(agent_id)->subscribe(observer);
}

void Agent_Network::unsubscribe_from_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer)
{
	std::scoped_lock lock(nodes_mutex_);
	_nodes_.at(agent_id)->unsubscribe(observer);
}

void Agent_Network::provide_message(message::Parsed_Message& msg)
{
	incoming_messages_.push(msg);
}

std::string Agent_Network::component_name()
{
	return "representational network";
}

void Agent_Network::run()
{
	std::unique_lock lock(alive_mutex_);

	message::Parsed_Message msg = incoming_messages_.stop_until_pop();
	if (msg.to) {
		std::scoped_lock Alock(nodes_mutex_);
		for (const auto& pair : _nodes_) {
			if (pair.second && pair.second->get_agent_id() == msg.to.value()) {
				pair.second->push_message(msg);
			}
		}
	}
	if (msg.new_id)
	{
		add_node(msg.new_id.value(), msg.connection_id);
		_nodes_.at(msg.new_id.value())->update_position(std::make_pair(msg.x_position.value(), msg.y_position.value()));

	}

	if (alive_) {
		lock.unlock();
		run();
	}
	else
		lock.unlock();
}

void Agent_Network::pause()
{
	_system_state_ = system_state::PAUSED;
	BOOST_LOG_TRIVIAL(info) << "Agent_Network named:" << name_ << " paused";
}

void Agent_Network::close()
{
	_system_state_ = system_state::TERMINATED;
	BOOST_LOG_TRIVIAL(info) << "Agent_Network named:" << name_ << " closed";
}