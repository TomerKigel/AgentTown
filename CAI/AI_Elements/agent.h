#pragma once
#include "Agent_Parameters.h"
#include <mutex>
#include <vector>
#include <memory>

#include "../Message_System/message.h"
#include "../Message_System/Message_Parser.h"
#include "Interfaces/Interface_Graphics_Observer.h"
#include "../AI_Elements/Message_Processor.h";
#include "../AI_Elements/Identification_Details.h";

class Agent
{
private:
	Agent_Parameters parameters_;
	std::vector<std::weak_ptr<Interface_Graphics_Observer>> observers;
	std::unique_ptr<Message_Processor> processor;
	Identification_Details info;

	//concurrency variables
	std::mutex param_mutex_;
	std::mutex observers_mutex_;

public:
	Agent();

	Agent(int id,int connection);

	Agent(Agent &other_agent);

	Agent& operator=(Agent& other);

	virtual ~Agent();

	void pause();

	//Mutators

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

	//Observer interface
	void subscribe(std::shared_ptr<Interface_Graphics_Observer> obs);

	void unsubscribe(std::shared_ptr<Interface_Graphics_Observer> obs);
};