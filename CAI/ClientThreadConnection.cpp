#include "ClientThreadConnection.h"


ClientThreadConnection::ClientThreadConnection(tcp::socket &&socket, std::unordered_map<int, std::shared_ptr<Connection>> &connections,int connection_id, std::shared_ptr<ThreadSafeQueue<message::message>> message_queue) : socket_(std::move(socket))
{
	this->message_queue = message_queue;
	this->connections_ = &connections;
	this->connection_id = connection_id;
	message_buffer.resize(MAX_MESSAGE_SIZE);
}

ClientThreadConnection::~ClientThreadConnection()
{
	disconnect();
}

int ClientThreadConnection::get_id() const
{
	return connection_id;
}

void ClientThreadConnection::run()
{
	read();
}

bool ClientThreadConnection::proccess_complete_message(const string &input,const size_t size)
{

	if (size > MAX_MESSAGE_SIZE)
		return false;
	//Find location of data
	int start_type_location = input.find(message::open_header);
	int end_type_location = input.find(message::close_header);

	if (start_type_location == -1 || end_type_location == -1  || start_type_location > end_type_location)
		return false;


	int start_message = input.find(message::open_message);
	int end_message = input.find(message::close_message);

	if (start_message == -1 || end_message == -1 || start_message > end_message)
		return false;

	//extract type
	incoming_msg.header.type = input.substr(start_type_location+ message::open_header.length(), end_type_location - message::close_header.length());
	
	std::vector<char> incoming_data(input.begin()+ start_message + message::open_message.length(), input.begin() + end_message);
	incoming_msg << incoming_data;
	

	message_queue->push(incoming_msg);
	incoming_msg.reset();
	try {
		send("{verification}$$$Got your message!&&&");
	}
	catch (std::exception e)
	{
		std::cout << "client serial number (" << connection_id << ") is not present" << endl;
		disconnect();
	}

	if (end_message < input.length())
		proccess_complete_message(input.substr(end_message+1), size - (end_message+1));

	return true;
}


void ClientThreadConnection::read() {
	try
	{
		auto self(shared_from_this());
		socket_.async_read_some(buffer(message_buffer.data(), message_buffer.size()),
			[self, this](std::error_code ec, std::size_t length)
		{
			if (!ec)
			{
				if (!proccess_complete_message(message_buffer.data(), length))
				{
					std::cout << "client serial number (" << connection_id << ") rejected" << endl;
					disconnect();
				}
				else
					read();
			}
			else
			{
				disconnect();
			}
		});
	}
	catch (std::exception e)
	{
		cout << e.what();
	}
}

void ClientThreadConnection::send(const string& message) {
	const string msg = message + "\n";
	boost::asio::write(socket_, boost::asio::buffer(message));
}


void ClientThreadConnection::send_all(const string& message) {
	for (auto& connection : *connections_)
		connection.second->send(message);
}


void ClientThreadConnection::send_channel(const std::string& message, string channel_name) {
	//TODO: make a send to all neighbours
	/*for (auto& connection : *connections_)
		connection.second->send(message);*/
	std::cout << "ok";
}


void ClientThreadConnection::disconnect() {
	
	try {
		socket_.close();
		connections_->erase(connection_id);
		std::cout << "client serial number (" << connection_id << ") disconnected" << endl;
	}
	catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}
