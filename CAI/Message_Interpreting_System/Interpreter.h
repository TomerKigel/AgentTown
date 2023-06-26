#pragma once
#include "../Message_System/message.h"
#include "boost/lexical_cast.hpp"
#include "../Framework/Interfaces/Component.h"
#include "../Framework/ConcreteMediator.h"
#include "../Message_System/MessageGenerator.h"

class Interpreter : public Component<message::message> , public interface_runnable
{
	bool alive;
	std::mutex alive_mutex;
	QueueManager<message::message> incoming_messages;
public:
	Interpreter()
	{

	}

	~Interpreter()
	{
		kill();
	}

	void run()
	{
		std::unique_lock lock(alive_mutex);
		
		message::message msg = incoming_messages.stop_until_pop();
		if (msg.direction == message::message::Out) {
			mediator_->push_message_out(msg);
		}
		else {
			message::ParsedMessage pmsg = message::parse_message(msg);
			if (pmsg.type.find("Error") != -1) {
				message::message error_message = MessageGenerator::generate_error_message(pmsg.type);
				mediator_->push_message_out(error_message);
			}
			else
			{
				//TODO: add analysis of parsed message to determine where it should be pushed.
				pmsg.destinations.emplace("representational network");
				mediator_->push_parsed_message(pmsg);
			}
		}
		if (alive) {
			lock.unlock();
			run();
		}
		else
			lock.unlock();
	}

	virtual void provide_message(message::message& msg)
	{
		incoming_messages.push(msg);
	}

	void kill()
	{
		std::scoped_lock lock(alive_mutex);
		alive = false;
	}
};