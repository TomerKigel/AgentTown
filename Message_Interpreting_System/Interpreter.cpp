#include "Interpreter.h"

Interpreter::Interpreter()
{
	alive_ = false;
	_system_state_ = system_state::PAUSED;
}

Interpreter::~Interpreter()
{
	close();
}

void Interpreter::activate_()
{
	std::unique_lock s_lock(system_state_mutex_);
	while (_system_state_ == system_state::PAUSED)
		system_state_condition_.wait(s_lock, [this] {return _system_state_ == system_state::RUNNING; });

	if (_system_state_ == system_state::TERMINATED) {
		s_lock.unlock();
		return;
	}
	s_lock.unlock();

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
		activate_();
	}
	else
		lock.unlock();
}

void Interpreter::provide_message(message::Message& msg)
{
	incoming_messages_.push(msg);
}
std::string Interpreter::component_name()
{
	return "interpreter";
}

void Interpreter::run()
{
	std::unique_lock s_lock(system_state_mutex_);
	_system_state_ = system_state::RUNNING;
	s_lock.unlock();
	BOOST_LOG_TRIVIAL(info) << "Interpreter system is now running";
	std::unique_lock lock(alive_mutex_);
	if (alive_ == false) {
		alive_ = true;
		alive_mutex_.unlock();
		activate_();
	}
}

void Interpreter::pause()
{
	std::scoped_lock s_lock(system_state_mutex_);
	_system_state_ = system_state::PAUSED;
	BOOST_LOG_TRIVIAL(info) << "Interpreter system paused";
}

void Interpreter::close()
{
	std::scoped_lock lock(alive_mutex_);
	alive_ = false;
	BOOST_LOG_TRIVIAL(info) << "Interpreter system closed";
}