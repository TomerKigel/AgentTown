#include "ClientThreadConnection.h"


ClientThreadConnection::ClientThreadConnection(tcp::socket &&socket, std::unordered_map<int, std::shared_ptr<Connection>> &connections,int connection_id_, std::shared_ptr<QueueManager<message::message>> message_pipeline_) : socket_(std::move(socket))
{
	this->message_pipeline_ = message_pipeline_;
	this->connections_ = &connections;
	this->connection_id_ = connection_id_;
	message_buffer.resize(MAX_MESSAGE_SIZE);
	message_pipeline_->add_out_queue(connection_id_);
}

ClientThreadConnection::~ClientThreadConnection()
{
	disconnect();
}

int ClientThreadConnection::get_id() const
{
	return connection_id_;
}

void ClientThreadConnection::run()
{
	out_messages_thread = std::thread([this]() {manage_outgoing_messages(); });
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
	incoming_msg.header.connection_id = this->connection_id_;

	message_pipeline_->in_push(incoming_msg);
	incoming_msg.reset();

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
					std::cout << "client serial number (" << connection_id_ << ") rejected" << endl;
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



void ClientThreadConnection::manage_outgoing_messages()
{
	std::optional<ThreadSafeQueue<message::message>*> out_message_queue_opt = message_pipeline_->get_out_queue(connection_id_);
	if (!out_message_queue_opt.has_value())
		return;

	ThreadSafeQueue<message::message> *out_message_queue = out_message_queue_opt.value();
	while (this->socket_.is_open()) {
		message::message msg = out_message_queue->until_pop();
		try {

			send(msg.to_string());
		}
		catch (std::exception e)
		{
			std::cout << "client serial number (" << connection_id_ << ") is not present" << endl;
			disconnect();
		}
	}
}


void ClientThreadConnection::disconnect() {
	
	try {
		socket_.close();
		out_messages_thread.join();
		connections_->erase(connection_id_);
		std::cout << "client serial number (" << connection_id_ << ") disconnected" << endl;
	}
	catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}
