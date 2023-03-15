#pragma once
#include "interface_runnable.h"
#include "interface_calculatable.h"
#include "message.h"
#include "agent_parameters.h"
#include "Movable.h"
#include <mutex>
#include <vector>

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
	agent();

	agent(int id);

	agent(agent &other_agent);

	virtual ~agent();

	bool add_neighbour(agent *neigh);

	bool remove_neighbour(agent* neigh);

	void run();

	unsigned int get_agent_id();

	void push_message(message::message &msg);

	virtual void process_message(message::message& msg) = 0;
};