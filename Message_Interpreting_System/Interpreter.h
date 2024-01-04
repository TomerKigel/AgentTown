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
	Interpreter();
	~Interpreter();
	void run();
	virtual void provide_message(message::Message& msg);
	std::string component_name();
	void pause();
	void close();
private:
	bool alive_;
	std::mutex alive_mutex_;
	Queue_Manager<message::Message> incoming_messages_;
};