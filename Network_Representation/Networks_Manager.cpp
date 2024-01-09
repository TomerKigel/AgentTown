#include "Networks_Manager.h"

Networks_Manager::Networks_Manager()
{
	create_network("DEFAULT");
}

void Networks_Manager::create_network(std::string network_name)
{
	if(agent_network_map_.count(network_name) == 0)
		agent_network_map_.insert(std::make_pair(network_name,new Agent_Network(network_name)));
	else
	{
		BOOST_LOG_TRIVIAL(info) << "No network was created because it already exists in function:Networks_Manager::create_network(std::string network_name)";
	}
}
void Networks_Manager::delete_network(std::string network_name)
{
	if (agent_network_map_.count(network_name) != 0 && network_name != "DEFAULT")
		agent_network_map_.erase(network_name);
	else if (network_name == "DEFAULT")
	{
		BOOST_LOG_TRIVIAL(info) << "'DEFAULT' network can't be removed in function Networks_Manager::delete_network(std::string network_name)";
	}
	else
	{
		//add throw here
		BOOST_LOG_TRIVIAL(error) << "'" << network_name << "' network can't be removed in function Networks_Manager::delete_network(std::string network_name) because it doesn't exist";
	}
}

void Networks_Manager::provide_message(message::Parsed_Message& msg)
{
	if (agent_network_map_.count(msg.network_name) == 0)
		return;
	else
		agent_network_map_.at(msg.network_name)->provide_message(msg);
}

std::string Networks_Manager::component_name()
{
	return "network manager";
}

void Networks_Manager::subscribe_to_network(Interface_Network_Observer* observer)
{
	for (std::pair<std::string, Agent_Network*> pair : agent_network_map_)
		pair.second->subscribe_to_network(observer);
}
void Networks_Manager::unsubscribe_from_network(const Interface_Network_Observer* observer)
{
	for (std::pair<std::string, Agent_Network*> pair : agent_network_map_)
		pair.second->unsubscribe_from_network(observer);
}

void Networks_Manager::run_all()
{
	for (std::pair<std::string, Agent_Network*> pair : agent_network_map_) 
			thread_network_map_.insert(std::make_pair(pair.first,
				std::thread([=]()
					{
						pair.second->run();
					})));
	
}
void Networks_Manager::pause_all()
{
	//unsafe, needs sync
	for (std::pair<std::string, Agent_Network*> pair : agent_network_map_)
		pair.second->pause();
}
void Networks_Manager::close_all()
{
	//unsafe, needs sync
	for (std::pair<std::string, Agent_Network*> pair : agent_network_map_)
		pair.second->close();
}