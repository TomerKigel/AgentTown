//#include "Agent.h"
//#include <thread>
//#include <mutex>
//
//
//void Agent::push_message(message::Parsed_Message& msg)
//{
//	processor->push_message(msg);
//}
//
//Agent::Agent()
//{
//	processor = std::make_unique<Message_Processor>(&parameters_, &observers);
//	parameters_.revive();
//	info.set_connection_id(0);
//	info.set_id(0);
//	processor->run();
//}
//
//Agent::Agent(int id,int connection_id)
//{
//	processor = std::make_unique<Message_Processor>(&parameters_, &observers);
//	parameters_.revive();
//	if (id < 0)
//		throw std::exception("Negative id in agent creation");
//	if(connection_id < 0)
//		throw std::exception("Negative connection_id in agent creation");
//	info.set_connection_id(connection_id);
//	info.set_id(id);
//	processor->run();
//}
//
//Agent::Agent(Agent& other_agent)
//{
//	processor = std::make_unique<Message_Processor>(&parameters_, &observers);
//	Agent_Parameters a(other_agent.parameters_);
//	parameters_ = a;
//	processor->run();
//}
//
//Agent& Agent::operator=(Agent& other)
//{
//	parameters_.revive();
//	Agent_Parameters a(other.parameters_);
//	parameters_ = a;
//	processor = std::make_unique<Message_Processor>(&parameters_, &observers);
//	return *this;
//}
//
//Agent::~Agent()
//{
//	this->parameters_.kill();
//}
//
//bool Agent::add_neighbour(int id) 
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	try {
//		return parameters_.add_neighbour(id);
//	}
//	catch (std::exception e)
//	{
//		std::cerr<<e.what();
//		return false;
//	}
//}
//
//bool Agent::remove_neighbour(int id) 
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	try {
//		return parameters_.remove_neighbour(id);
//	}
//	catch (std::exception e)
//	{
//		std::cerr<<e.what();
//		return false;
//	}
//}
//
//void Agent::set_connection_id(int id)
//{
//	info.set_connection_id(id);
//}
//
//void Agent::set_id(int id)
//{
//	info.set_id(id);
//}
//
//unsigned int Agent::get_connection_id()
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	try {
//		return info.get_connection_id();
//	}
//	catch (std::exception e)
//	{
//		std::cerr<<e.what();
//		throw e;
//	}
//}
//
//unsigned int Agent::get_agent_id()
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	try {
//		return info.get_id();
//	}
//	catch (std::exception e)
//	{
//		std::cerr<<e.what();
//		throw e;
//	}
//}
//
//
//void Agent::pause()
//{
//
//}
//
//void Agent::subscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
//{
//	std::lock_guard<std::mutex>lock(observers_mutex_);
//	observers.push_back(obs);
//}
//
//void Agent::unsubscribe(std::shared_ptr<Interface_Graphics_Observer> obs)
//{
//	std::lock_guard<std::mutex>lock(observers_mutex_);
//	std::remove_if(observers.begin(), observers.end(), [obs](const std::weak_ptr<Interface_Graphics_Observer>& a) {return a.lock() == obs; });
//}
//
//
//std::pair<double, double> Agent::get_position()
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	return parameters_.getLocation();
//}
//
//void Agent::update_position(std::pair<double, double> x_y)
//{
//	std::lock_guard<std::mutex>lock(param_mutex_);
//	parameters_.setLocation(x_y.first,x_y.second);
//	std::lock_guard<std::mutex>olock(observers_mutex_);
//	for (std::weak_ptr<Interface_Graphics_Observer> obs : observers)
//		obs.lock()->update_position(x_y.first, x_y.second);
//}
