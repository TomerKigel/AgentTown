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

#include <string>
#include <iostream>
#include "boost/asio.hpp"
#include <mutex>
#include "Connection.h"
#include "message.h"
#include "System.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace boost::asio;
using ip::tcp;

class MainServer : public System<message::Message>
{
public:

	/// <summary>
	/// binds context and endpoint to tcp::acceptor <para />
	/// default endpoint details:<para />
	/// ip:127.0.0.1<para />
	/// port:7777<para />
	/// to rebind the endpoint see:<see cref="bind_server"/>
	/// </summary>
	/// <param name="io_context">- the boost::asio::io_context</param>
	/// <param name="endpoint">- the ip::tcp::endpoint</param>
	MainServer();

	/// <summary>
	/// default destructor
	/// </summary>
	virtual ~MainServer();

	/// <summary>
	/// allows rebinding the endpoint to the server. <para />
	/// useful for instantiating a server on the stack and later rebinding it if inital binding is impossible
	/// </summary>
	/// <param name="endpoint"> - the ip::tcp::endpoint to rebind to</param>
	void bind_server(std::string host, int port);

	/// <summary>
	/// Initiate the server
	/// </summary>
	bool run();

	/// <summary>
	/// pause the server and the io_context
	/// </summary>
	void pause();

	/// <summary>
	/// pass a message to this component for processing
	/// </summary>
	/// <param name="msg"> - the message to be passed</param>
	void provide_message(message::Message& msg);

	/// <summary>
	/// an identification function to return the name of this component
	/// </summary>
	/// <returns>the name of the component</returns>
	std::string component_name();


	/// <summary>
	/// shutdown server
	/// </summary>
	void close();

private:
	/// <summary>
	/// A-sync wait for a client connection
	/// priming the io_context  <para />
	/// </summary>
	void wait_for_connection();


	//
	std::string host_ = "127.0.0.1";
	int port_ = 7777;

	boost::asio::ip::tcp::endpoint end_point_{ boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host_), port_) };
	boost::asio::io_context io_context_;
	tcp::acceptor acceptor_;

	std::unordered_map<int, std::shared_ptr<Connection>> connections_;
	int running_connection_id_;
	std::vector<std::thread> threads_;
	std::thread context_thread_;
};
