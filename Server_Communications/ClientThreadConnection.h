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
#include "Connection.h"
#include <boost/asio.hpp>
#include <iostream>
#include <unordered_map>
#include "Queue_Manager.h"
#include "message.h"
#include "Message_Generator.h"
#include "System.h"
#include <mutex>

#define MAX_MESSAGE_SIZE 10240

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace boost::asio;
using ip::tcp;


class ClientThreadConnection : virtual public Connection, public std::enable_shared_from_this<ClientThreadConnection>, public System<message::Message>
{
public:
	ClientThreadConnection(tcp::socket&& socket, std::unordered_map<int, std::shared_ptr<Connection>>& connections, int connection_id_, Interface_Mediator* mediator_);

	~ClientThreadConnection();

	bool proccess_complete_message(const string& input, const size_t size);

	int get_id() const;

	void run();

	void send(const std::string& message);

	void send_to_id_list(const std::string& message, const std::vector<int> id_list);

	void send_all(const std::string& message);

	void read();

	void provide_message(message::Message& msg);

	std::string component_name();

	void disconnect();

private:
	int connection_id_;
	tcp::socket socket_;
	std::unordered_map<int, std::shared_ptr<Connection>>* connections_;
	message::Message incoming_msg;
	std::vector<char> message_buffer;

	std::mutex send_mutex;

};