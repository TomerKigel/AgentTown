#include "Agent.h"
#include <thread>
#include <mutex>

void Agent::event_controller_()
{
	std::unique_lock<std::mutex>alock(alive_mutex_);

	std::unique_lock<std::mutex> lock(param_mutex_);
	while(parameters_.message_queue_.size() <= 0)
		cv_.wait(lock, [this] {return parameters_.message_queue_.size() > 0; });
	
	lock.unlock();

	std::optional<message::ParsedMessage> msg = parameters_.message_queue_.pop();
	if (msg)
		process_message(msg.value());

	if (alive_) {
		alock.unlock();
		event_controller_();
	}
	else
		alock.unlock();
	
}

void Agent::push_message(message::ParsedMessage& msg)
{
	std::unique_lock<std::mutex>lock(param_mutex_);
	parameters_.message_queue_.push(msg);
	lock.unlock();
	cv_.notify_all();
}


Agent::Agent(int id,int connection_id)
{
	alive_ = true;
	Agent_Parameters a(id, connection_id);
	parameters_ = a;
}

Agent::Agent()
{
	alive_ = true;
	Agent_Parameters a;
	parameters_ = a;
}

Agent::Agent(Agent& other_agent) : alive_(other_agent.alive_) 
{
	Agent_Parameters a(other_agent.parameters_);
	parameters_ = a;
}

Agent& Agent::operator=(Agent& other)
{
	alive_ = other.alive_;
	Agent_Parameters a(other.parameters_);
	parameters_ = a;
	return *this;
}

Agent::~Agent()
{
	std::unique_lock<std::mutex>alock(alive_mutex_);
	this->alive_ = false;
	alock.unlock();
	cv_.notify_all();
	agent_thread_.join();
}

bool Agent::add_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	return parameters_.add_neighbour(id);
}

bool Agent::remove_neighbour(int id)
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	return parameters_.remove_neighbour(id);
}

unsigned int Agent::get_connection_id()
{
	return parameters_.get_connection_id();
}

unsigned int Agent::get_agent_id()
{
	std::lock_guard<std::mutex>lock(param_mutex_);
	return parameters_.get_id();
}

void Agent::run()
{
	parameters_.close_for_change();
	agent_thread_ = std::thread([this]() { event_controller_(); });
}

void Agent::subscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
{
	observers.push_back(obs);
}

void Agent::unsubscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
{
	std::remove_if(observers.begin(), observers.end(), [obs](const std::shared_ptr<Interface_Graphics_Observer>& a) {return a == obs; });
}


void Agent::process_message(message::ParsedMessage& msg)
{
	if (msg.x_position && msg.y_position)
	{
		for(std::shared_ptr<Interface_Graphics_Observer> obs : observers)
				obs->update_position(msg.x_position.value(), msg.y_position.value());
		parameters_.setLocation(msg.x_position.value(), msg.y_position.value());
	}
	if (msg.type == "disconnect") {
		for (std::shared_ptr<Interface_Graphics_Observer> obs : observers)
			obs->kill();
		destroy();
	}
}

std::pair<double, double> Agent::get_position()
{
	return parameters_.getLocation();
}

void Agent::update_position(std::pair<double, double> x_y)
{
	parameters_.setLocation(x_y.first,x_y.second);
	for (std::shared_ptr<Interface_Graphics_Observer> obs : observers)
		obs->update_position(x_y.first, x_y.second);
}