#pragma once

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include "Connection.h"
#include "message.h"
#include "ThreadSafeQueue.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace boost::asio;
using ip::tcp;



class MainServer
{
private:
	tcp::acceptor acceptor_;

	std::unordered_map<int,std::shared_ptr<Connection>> connections_;
	int running_connection_id;
	std::vector<std::thread> threads;
	std::shared_ptr<ThreadSafeQueue<message::message>> message_queue;

public:
	MainServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint, std::shared_ptr<ThreadSafeQueue<message::message>> message_queue);

	virtual ~MainServer();

	void wait_for_connection();

	bool start();

	void close();
}; 
