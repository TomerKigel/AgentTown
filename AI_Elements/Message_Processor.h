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

#include <thread>
#include <mutex>
#include <optional>

#include "message.h"
#include "Interface_Runnable.h"
#include "Interface_Graphics_Observer.h"
#include "Message_Parser.h"
#include "Queue_Manager.h"
#include "Agent_Parameters.h"

class Message_Processor : public Interface_Runnable
{
public:
	Message_Processor(Agent_Parameters* params, std::vector<std::weak_ptr<Interface_Graphics_Observer>>* observers_)
	{
		parameters_ = params;
		observers_ = observers_;
	}
	~Message_Processor()
	{
		agent_thread_.join();
	}
	//Message passing
	inline void push_message(message::Parsed_Message& msg);

	inline void process_message(message::Parsed_Message& msg);

	//Interface_Runnable concurrent interface
	inline void run();

private:
	inline void event_controller_();

	//concurrency variables
	std::mutex param_mutex_;
	std::mutex observers_mutex_;
	std::condition_variable cv_;
	std::thread agent_thread_;

	//Message queue
	Queue_Manager<message::Parsed_Message> message_queue_;

	//object state ptr
	Agent_Parameters* parameters_; // maybe weak ptr 

	std::vector<std::weak_ptr<Interface_Graphics_Observer>>* observers_;
};

void Message_Processor::event_controller_()
{
	std::unique_lock<std::mutex> lock(param_mutex_);
	while (message_queue_.size() <= 0)
		cv_.wait(lock, [this] {return message_queue_.size() > 0; });

	lock.unlock();

	std::optional<message::Parsed_Message> msg = message_queue_.pop();
	if (msg)
		process_message(msg.value());

	if (parameters_->is_alive()) {
		event_controller_();
	}
}

void Message_Processor::push_message(message::Parsed_Message& msg)
{
	std::unique_lock<std::mutex>lock(param_mutex_);
	message_queue_.push(msg);
	lock.unlock();
	cv_.notify_all();
}

void Message_Processor::run()
{
	parameters_->close_for_change();
	agent_thread_ = std::thread([this]() { event_controller_(); });
}

void Message_Processor::process_message(message::Parsed_Message& msg)
{
	std::lock_guard<std::mutex>lock(observers_mutex_);
	if (msg.x_position && msg.y_position)
	{
		for (std::weak_ptr<Interface_Graphics_Observer> obs : *observers_)
			obs.lock()->update_position(msg.x_position.value(), msg.y_position.value());
		parameters_->setLocation(msg.x_position.value(), msg.y_position.value());
	}
	if (msg.type == "disconnect") {
		for (std::weak_ptr<Interface_Graphics_Observer> obs : *observers_)
			obs.lock()->kill();
		parameters_->kill();
	}
}