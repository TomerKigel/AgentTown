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
#include "ClientThreadConnection.h"

ClientThreadConnection::ClientThreadConnection(tcp::socket&& socket, std::unordered_map<int, std::shared_ptr<Connection>>& connections, int connection_id_, Interface_Mediator* mediator_) : socket_(std::move(socket))
{
	this->mediator_ = mediator_;
	this->connections_ = &connections;
	this->connection_id_ = connection_id_;
	message_buffer.resize(MAX_MESSAGE_SIZE);
}

ClientThreadConnection::~ClientThreadConnection()
{
	if(connections_->count(connection_id_) != 0)
		disconnect();
}

int ClientThreadConnection::get_id() const
{
	return connection_id_;
}

void ClientThreadConnection::run()
{
	read();
}

bool ClientThreadConnection::proccess_complete_message(const string& input, const size_t size)
{

	if (size > MAX_MESSAGE_SIZE)
		return false;

	//Find location of data
	int start_type_location = input.find(message::open_header);
	int end_type_location = input.find(message::close_header);

	if (start_type_location == -1 || end_type_location == -1 || start_type_location > end_type_location)
		return false;


	int start_message = input.find(message::open_message);
	int end_message = input.find(message::close_message);

	if (start_message == -1 || end_message == -1 || start_message > end_message)
		return false;

	//extract type
	incoming_msg.header.type = input.substr(start_type_location + message::open_header.length(), end_type_location - message::close_header.length());

	std::vector<char> incoming_data(input.begin() + start_message + message::open_message.length(), input.begin() + end_message);
	incoming_msg << incoming_data;
	incoming_msg.header.connection_id = this->connection_id_;
	incoming_msg.direction = message::Message::message_direction::In;

	mediator_->push_message(incoming_msg);
	message::reset(incoming_msg);

	if (end_message < input.length())
		proccess_complete_message(input.substr(end_message + 1), size - (end_message + 1));

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

void ClientThreadConnection::send(const string& message){
	std::scoped_lock<std::mutex> lock(send_mutex);
	boost::asio::write(socket_, boost::asio::buffer(message));
}


void ClientThreadConnection::send_all(const string& message) {
	for (auto& connection : *connections_)
		connection.second->send(message);
}

void ClientThreadConnection::send_to_id_list(const std::string& message, const std::vector<int> id_list)
{
	for (auto& connection : *connections_)
		if(std::find(id_list.begin(), id_list.end(),connection.first) != id_list.end())
			connection.second->send(message);
}


void ClientThreadConnection::disconnect() {

	try {
		socket_.close();
		connections_->erase(connection_id_);
		mediator_->push_message(Message_Generator::generate_disconnect_message(connection_id_));
		std::cout << "client serial number (" << connection_id_ << ") disconnected" << endl;
	}
	catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}


void ClientThreadConnection::provide_message(message::Message& msg)
{
	send(message::to_string(msg));
}

std::string ClientThreadConnection::component_name()
{
	return "connection id:" + this->connection_id_;
}
