#pragma once

#include <string>
#include <iostream>
#include "boost/asio.hpp"
#include <mutex>
#include "Connection.h"
#include "../CAI/Message_System/message.h"
#include "Component.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace boost::asio;
using ip::tcp;

class MainServer : public Component<message::Message>
{
private:
	tcp::acceptor acceptor_;

	std::unordered_map<int, std::shared_ptr<Connection>> connections_;
	int running_connection_id_;
	std::vector<std::thread> threads_;

public:
	MainServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint);

	virtual ~MainServer();

	void wait_for_connection();

	bool run();

	void pause();

	void provide_message(message::Message& msg);

	std::string service_name();

	void close();
};
