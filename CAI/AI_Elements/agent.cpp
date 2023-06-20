#include "agent.h"
#include <thread>
#include <mutex>

void agent::EventController()
{
	while (alive)
	{
		std::unique_lock<std::mutex> lock(param_mutex);
		if(parameters_.message_queue_.size() <= 0)
			cv.wait(lock, [this] {return parameters_.message_queue_.size() > 0; });
		
		if (!alive)
			return;

		std::optional<message::ParsedMessage> msg = parameters_.message_queue_.pop();
		if(msg)
			process_message(msg.value());
	}
}

void agent::push_message(message::ParsedMessage& msg)
{
	std::unique_lock<std::mutex>lock(param_mutex);
	parameters_.message_queue_.push(msg);
	lock.unlock();
	cv.notify_all();
}


agent::agent(int id,int connection_id)
{
	alive = true;
	agent_parameters a(id, connection_id);
	parameters_ = a;
}

agent::agent()
{
	alive = true;
	agent_parameters a;
	parameters_ = a;
}

agent::agent(agent& other_agent) : alive(other_agent.alive) 
{
	agent_parameters a(other_agent.parameters_);
	parameters_ = a;
}

agent& agent::operator=(agent& other)
{
	alive = other.alive;
	agent_parameters a(other.parameters_);
	parameters_ = a;
	return *this;
}

agent::~agent()
{
	std::unique_lock<std::mutex>alock(alive_mutex);
	this->alive = false;
	alock.unlock();
	cv.notify_all();
	agent_thread.join();
}

bool agent::add_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex);
	return parameters_.add_neighbour(id);
}

bool agent::remove_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex);
	return parameters_.remove_neighbour(id);
}

unsigned int agent::get_connection_id()
{
	return parameters_.get_connection_id();
}

unsigned int agent::get_agent_id()
{
	std::lock_guard<std::mutex>lock(param_mutex);
	return parameters_.get_id();
}

void agent::run()
{
	parameters_.close_for_change();
	std::cout << "" << "running"; 
	agent_thread = std::thread([this]() { EventController(); });
}


void agent::process_message(message::ParsedMessage& msg)
{
	if (msg.x_position && msg.y_position)
	{
		observer->update_position(msg.x_position.value(), msg.y_position.value());
		parameters_.setLocation(msg.x_position.value(), msg.y_position.value());
		/*getAABB()->SetTL(msg.x_position.value(), msg.y_position.value());
		getAABB()->SetBR(msg.x_position.value() + getAABB()->GetLen(), msg.y_position.value() + getAABB()->GetWid());*/
	}
	if (msg.type == "disconnect") {
		destroy();
		observer->kill();
	}
}