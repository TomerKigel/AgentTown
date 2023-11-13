#pragma once
#include "message.h"
#include "boost/lexical_cast.hpp"
#include "Component.h"
#include "Message_Generator.h"
#include "Interface_Runnable.h"
#include "Queue_Manager.h"
#include <mutex>
#include "Message_Parser.h"

class Interpreter : public Component<message::Message>, public Interface_Runnable
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