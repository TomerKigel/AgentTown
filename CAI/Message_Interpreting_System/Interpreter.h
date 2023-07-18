#pragma once
#include "../Message_System/message.h"
#include "boost/lexical_cast.hpp"
#include "../Framework/Interfaces/Component.h"
#include "../Framework/Concrete_Mediator.h"
#include "../Message_System/Message_Generator.h"

class Interpreter : public Component<message::Message> , public Interface_Runnable
{
	bool alive_;
	std::mutex alive_mutex_;
	Queue_Manager<message::Message> incoming_messages_;

public:
	Interpreter()
	{
		alive_ = true;
		system_state_ = system_state::RUNNING;
	}

	~Interpreter()
	{
		close();
	}

	void run()
	{
		std::unique_lock lock(alive_mutex_);
		
		message::Message msg = incoming_messages_.stop_until_pop();
		if (msg.direction == message::Message::message_direction::Out) {
			mediator_->push_message(msg);
		}
		else {
			message::Parsed_Message pmsg = message::parse_message(msg);
			if (pmsg.type.find("Error") != -1) {
				message::Message error_message = Message_Generator::generate_error_message(pmsg.type);
				mediator_->push_message(error_message);
			}
			else
			{
				//TODO: add analysis of parsed message to determine where it should be pushed.
				pmsg.destinations.emplace("representational network");
				mediator_->push_parsed_message(pmsg);
			}
		}
		if (alive_) {
			lock.unlock();
			run();
		}
		else
			lock.unlock();
	}

	virtual void provide_message(message::Message& msg)
	{
		incoming_messages_.push(msg);
	}
	std::string service_name()
	{
		return "interpreter";
	}


	void pause()
	{
		system_state_ = system_state::PAUSED;
	}

	void close()
	{
		std::scoped_lock lock(alive_mutex_);
		alive_ = false;
	}
};