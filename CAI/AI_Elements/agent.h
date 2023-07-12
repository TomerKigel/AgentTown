#pragma once
#include "Agent_Parameters.h"
#include <mutex>
#include <vector>
#include <memory>

#include "../Framework/Interfaces/Interface_Runnable.h"
#include "../AI_Elements/Interfaces/interface_calculatable.h"
#include "../Message_System/message.h"
#include "../Message_System/Message_Parser.h"
#include "Interfaces/Interface_Graphics_Observer.h"

class Agent : public Interface_Runnable
{
private:
	bool alive_;
	Agent_Parameters parameters_; // pimpl-idiom for Agent parameters

	//concurrency variables
	std::mutex alive_mutex_;
	std::mutex param_mutex_;
	std::mutex observers_mutex_;
	std::condition_variable cv_;
	std::thread agent_thread_;

	std::vector<std::weak_ptr<Interface_Graphics_Observer>> observers;

	// main loop
	void event_controller_();
public:
	//Actor Dctor Cctor
	Agent();

	Agent(int id,int connection);

	Agent(Agent &other_agent);

	//Agent(Agent&& other_agent) = default;

	Agent& operator=(Agent& other);

	virtual ~Agent();

	//Interface_Runnable concurrent interface

	void run();

	//Mutators
	virtual void destroy(){
		alive_ = false;
	}

	bool add_neighbour(int id);

	bool remove_neighbour(int id);

	void update_position(std::pair<double, double> x_y);

	void set_connection_id(int id);

	void set_id(int id);
	//accessors
	unsigned int get_agent_id();

	unsigned int get_connection_id();

	std::pair<double, double> get_position();


	//Message passing
	void push_message(message::Parsed_Message& msg);

	virtual void process_message(message::Parsed_Message& msg);

	//Observer interface
	void subscribe(std::shared_ptr<Interface_Graphics_Observer> obs);

	void unsubscribe(std::shared_ptr<Interface_Graphics_Observer> obs);
};