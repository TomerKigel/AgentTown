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
#include "MainServer.h"
#include "ClientThreadConnection.h"


MainServer::MainServer() : acceptor_(io_context_, end_point_)
{
	running_connection_id_ = 1;
	system_state_ = system_state::RUNNING;
}

void MainServer::bind_server(std::string host, int port)
{

	host_ = host;
	port_ = port;

	acceptor_.close(); // Close the existing acceptor

	end_point_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port); // rebind the endpoint;
	try {
		acceptor_.open(end_point_.protocol());
		acceptor_.bind(end_point_);
		acceptor_.listen();
	}
	catch (std::exception& e) {
		std::cerr << "Error rebinding acceptor: " << e.what() << std::endl;
	}
}

MainServer::~MainServer() {
	close();
}

bool MainServer::run() {
	std::cout << "Main-Server starting" << std::endl;
	context_thread_ = std::thread([this]() { io_context_.run(); });
	try {
		system_state_ = system_state::RUNNING;
		wait_for_connection();
	}
	catch (std::exception& e) {
		std::cerr << "Could not initiate server." << std::endl;
		return false;
	}
	return true;
}

void MainServer::pause()
{
	system_state_ = system_state::PAUSED;
	acceptor_.cancel();
	std::cout << "Main-Server paused" << std::endl;
}


void MainServer::wait_for_connection()
{
	acceptor_.async_accept(
		[this](boost::system::error_code ec, tcp::socket socket)
		{
			if (!ec)
			{
				cout << "Established connection with connection id: " << running_connection_id_ << endl;
				auto connection_ptr = std::make_shared<ClientThreadConnection>(std::move(socket), connections_, running_connection_id_++, mediator_);
				connections_.insert(std::make_pair(running_connection_id_, connection_ptr));
				connection_ptr->run();
			}
			if(system_state_ == system_state::RUNNING)
				wait_for_connection();
		});
}


void MainServer::close() {
	try {
		system_state_ = system_state::TERMINATED;
		acceptor_.close();
		for (auto& connection : connections_)
			connection.second->disconnect();
		context_thread_.join();
	}
	catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}


void MainServer::provide_message(message::Message& msg)
{
	connections_.at(msg.header.connection_id)->send(message::to_string(msg));
}

std::string MainServer::component_name()
{
	return "main server";
}
