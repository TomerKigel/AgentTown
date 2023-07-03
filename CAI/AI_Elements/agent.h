#pragma once
#include "agent_parameters.h"
#include <mutex>
#include <vector>

#include "../Framework/Interfaces/interface_runnable.h"
#include "../AI_Elements/Interfaces/interface_calculatable.h"
#include "../Message_System/message.h"
#include "../Message_System/MessageParser.h"
#include "Interfaces/GraphicsObserver.h"
class agent : public interface_runnable
{
private:
	bool alive;
	std::mutex alive_mutex;
	agent_parameters parameters_; // pimpl-idiom for agent parameters
	std::mutex param_mutex;
	std::condition_variable cv;
	std::thread agent_thread;

	std::vector<std::shared_ptr<GraphicsObserver>> observers;

	void EventController();

public:
	virtual void destroy() { 
		alive = false;
	}

	std::pair<double,double> get_position();

	agent();

	agent(int id,int connection);

	agent(agent &other_agent);

	agent& operator=(agent& other);

	virtual ~agent();

	bool add_neighbour(int id);

	bool remove_neighbour(int id);

	void run();

	unsigned int get_agent_id();

	unsigned int get_connection_id();

	void update_position(std::pair<double,double> x_y);

	void push_message(message::ParsedMessage& msg);

	virtual void process_message(message::ParsedMessage& msg);

	void subscribe(std::shared_ptr<GraphicsObserver> obs);

	void unsubscribe(std::shared_ptr<GraphicsObserver> obs);
};