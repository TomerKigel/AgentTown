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
		
	/*	std::unique_lock<std::mutex>tlock(alive_mutex);*/
		if (!alive)
			return;
		/*tlock.release();*/

		message::message msg = parameters_.message_queue_.front();
		parameters_.message_queue_.pop();
		process_message(msg);
		/*std::scoped_lock<std::mutex>alock(alive_mutex);*/
		if (!alive)
			return;
	}
}

void agent::push_message(message::message &msg)
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
	//events_thread = new std::thread(&agent::EventController, this);
}

agent::agent()
{
	alive = true;
	agent_parameters a;
	parameters_ = a;
	//events_thread = new std::thread(&agent::EventController, this);
}

agent::agent(agent& other_agent) : alive(other_agent.alive) 
{
	agent_parameters a(other_agent.parameters_);
	parameters_ = a;
	//events_thread = new std::thread(&agent::EventController, this);
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

unsigned int  agent::get_connection_id()
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

