#include "agent.h"
#include <thread>
#include <mutex>

void agent::EventController()
{
	std::unique_lock<std::mutex>alock(alive_mutex);

	std::unique_lock<std::mutex> lock(param_mutex);
	while(parameters_.message_queue_.size() <= 0)
		cv.wait(lock, [this] {return parameters_.message_queue_.size() > 0; });
	
	lock.unlock();

	std::optional<message::ParsedMessage> msg = parameters_.message_queue_.pop();
	if (msg)
		process_message(msg.value());

	if (alive) {
		alock.unlock();
		EventController();
	}
	else
		alock.unlock();
	
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

void agent::subscribe(std::shared_ptr<GraphicsObserver> obs)
{
	observers.push_back(obs);
}

void agent::unsubscribe(std::shared_ptr<GraphicsObserver> obs)
{
	std::remove_if(observers.begin(), observers.end(), [obs](const std::shared_ptr<GraphicsObserver>& a) {return a == obs; });
}


void agent::process_message(message::ParsedMessage& msg)
{
	if (msg.x_position && msg.y_position)
	{
		for(std::shared_ptr<GraphicsObserver> obs : observers)
				obs->update_position(msg.x_position.value(), msg.y_position.value());
		parameters_.setLocation(msg.x_position.value(), msg.y_position.value());
	}
	if (msg.type == "disconnect") {
		for (std::shared_ptr<GraphicsObserver> obs : observers)
			obs->kill();
		destroy();
	}
}

std::pair<double, double> agent::get_position()
{
	return parameters_.getLocation();
}

void agent::update_position(std::pair<double, double> x_y)
{
	parameters_.setLocation(x_y.first,x_y.second);
	for (std::shared_ptr<GraphicsObserver> obs : observers)
		obs->update_position(x_y.first, x_y.second);
}