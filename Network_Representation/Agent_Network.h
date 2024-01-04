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
#include "Debug.h"

#include "Network.h"
#include "Agent.h"
#include "System.h"

class Agent_Network : public Network<std::shared_ptr<Agent>>, public System<message::Parsed_Message>, public Interface_Runnable
{
public:
	Agent_Network(std::string name_ = "DEFAULT");

	void add_node(int id, int connection);
	void remove_node(int id);

	void add_neighbour_to_agent(int agent_id, int neighbour_id);
	void remove_neighbour_to_agent(int agent_id, int neighbour_id);

	void subscribe_to_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer);
	void unsubscribe_from_agent(int agent_id, std::shared_ptr<Interface_Graphics_Observer> observer);

	virtual void provide_message(message::Parsed_Message& msg);

	std::string component_name();

	void run();
	void pause();
	void close();
private:
	bool alive_;
	std::mutex alive_mutex_;
	std::string name_;
	Queue_Manager<message::Parsed_Message> incoming_messages_;
};