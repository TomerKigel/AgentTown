#pragma once
#include "agent_parameters.h"
#include <mutex>
#include <vector>

#include "../Framework/Interfaces/interface_runnable.h"
#include "../AI_Elements/Interfaces/interface_calculatable.h"
#include "../Message_System/message.h"
#include "../Message_System/MessageParser.h"
#include "../Graphics_Engine/Objects/Movable.h"

class agent : public interface_runnable , public Movable
{
private:
	bool alive;
	std::mutex alive_mutex;
	agent_parameters parameters_; // pimpl-idiom for agent parameters
	std::mutex param_mutex;
	std::condition_variable cv;
	std::thread agent_thread;

	void EventController();

public:
	virtual void destroy() { destruct = true; alive = false;}

	agent();

	agent(int id,int connection);

	agent(agent &other_agent);

	virtual ~agent();

	bool add_neighbour(int id);

	bool remove_neighbour(int id);

	void run();

	unsigned int get_agent_id();

	unsigned int get_connection_id();

	void push_message(message::ParsedMessage& msg);

	virtual void process_message(message::ParsedMessage& msg) = 0;

};