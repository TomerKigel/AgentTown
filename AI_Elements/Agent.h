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

#include <mutex>
#include <vector>
#include <memory>

#include "message.h"
#include "Message_Parser.h"
#include "Interface_Graphics_Observer.h"
#include "Agent_Parameters.h"
#include "Message_Processor.h"
#include "Identification_Details.h"

class Agent
{
public:
	Agent();

	Agent(int id, int connection);

	Agent(Agent& other_agent);

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

private:
	Agent_Parameters parameters_;
	std::vector<std::weak_ptr<Interface_Graphics_Observer>> observers_;
	std::unique_ptr<Message_Processor> processor_;
	Identification_Details info_;

	//concurrency variables
	std::mutex param_mutex_;
	std::mutex observers_mutex_;
};