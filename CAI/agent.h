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

protected:
	virtual void destroy() { destruct = true; alive = false;}
public:
	agent();

	agent(int id,int connection);

	agent(agent &other_agent);

	virtual ~agent();

	bool add_neighbour(int id);

	bool remove_neighbour(int id);

	void run();

	unsigned int get_agent_id();

	unsigned int get_connection_id();

	void push_message(message::message &msg);

	virtual void process_message(message::message& msg) = 0;

};