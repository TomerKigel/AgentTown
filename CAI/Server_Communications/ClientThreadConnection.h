#pragma once
#include "../Server_Communications/Interfaces/Connection.h"
#include "../Message_System/message.h"
#include <boost/asio.hpp>
#include <iostream>
#include "../Message_System/QueueManager.h"
#include "../Framework/Interfaces/Component.h"

#define MAX_MESSAGE_SIZE 10240

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace boost::asio;
using ip::tcp;


class ClientThreadConnection : virtual public Connection , public std::enable_shared_from_this<ClientThreadConnection>,public Component<message::message>
{
private: 
	int connection_id_;
	tcp::socket socket_;
	std::unordered_map<int, std::shared_ptr<Connection>> *connections_;
	message::message incoming_msg;
	std::vector<char> message_buffer;

	std::mutex send_mutex;
	
public:
	ClientThreadConnection(tcp::socket &&socket, std::unordered_map<int, std::shared_ptr<Connection>> &connections,int connection_id_, Mediator *mediator_);

	~ClientThreadConnection();

	bool proccess_complete_message(const string& input, const size_t size);

	int get_id() const;

	void run();

	void send(const std::string& message);

	void send_channel(const std::string& message, string channel_name);

	void send_all(const std::string& message);

	void read();

	void provide_message(message::message& msg);

	std::string service_name();

	void disconnect();

};