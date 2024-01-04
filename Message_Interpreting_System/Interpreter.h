/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/
#pragma once

#define BOOST_ALL_DYN_LINK

#include <boost/log/trivial.hpp>
#include "debug.h"

#include "message.h"
#include "boost/lexical_cast.hpp"
#include "System.h"
#include "Message_Generator.h"
#include "Interface_Runnable.h"
#include "Queue_Manager.h"
#include <mutex>
#include "Message_Parser.h"

class Interpreter : public System<message::Message>, public Interface_Runnable
{
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
				BOOST_LOG_TRIVIAL(warning) << "incoming message type not found,error message generated to be sent to client";
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
	std::string component_name()
	{
		return "interpreter";
	}
	void pause()
	{
		system_state_ = system_state::PAUSED;
		BOOST_LOG_TRIVIAL(info) << "Interpreter system paused";
	}

	void close()
	{
		std::scoped_lock lock(alive_mutex_);
		alive_ = false;
		BOOST_LOG_TRIVIAL(info) << "Interpreter system closed";
	}
private:
	bool alive_;
	std::mutex alive_mutex_;
	Queue_Manager<message::Message> incoming_messages_;
};