#pragma once
#include "Network.h"
#include "Agent.h"
#include "System.h"

class Agent_Network : public Network<std::shared_ptr<Agent>>, public System<message::Parsed_Message>, public Interface_Runnable
{
public:
	Agent_Network();

	void add_node(int id, int connection);
	void remove_node(int id);

	void add_neighbour_to_agent(int agent_id, int neighbour_id);
	void remove_neighbour_to_agent(int agent_id, int neighbour_id);

	void subscribe_to_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer);
	void unsubscribe_from_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer);

	virtual void provide_message(message::Parsed_Message& msg);

	std::string component_name();

	void run();
	void pause();
	void close();
private:
	bool alive_;
	std::mutex alive_mutex_;
	Queue_Manager<message::Parsed_Message> incoming_messages_;
};