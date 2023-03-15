#include "MainServer.h"
#include "ClientThreadConnection.h"


MainServer::MainServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint, std::shared_ptr<ThreadSafeQueue<message::message>> message_queue) : acceptor_(io_context, endpoint)
{
	running_connection_id = 0;
	this->message_queue = message_queue;
}


MainServer::~MainServer() {
	close();
}

bool MainServer::start() {
	std::cout << "Main-Server starting" << std::endl;
	try {
		wait_for_connection();
	}
	catch (std::exception& e) {
		std::cerr << "Could not initiate server." << std::endl;
		return false;
	}
	return true;
}


void MainServer::wait_for_connection()
{
			acceptor_.async_accept(
				[this](boost::system::error_code ec, tcp::socket socket)
			{
				if (!ec)
				{
					cout << "Established connection with connection id: " << running_connection_id << endl;
					auto connection_ptr = std::make_shared<ClientThreadConnection>(std::move(socket), connections_, running_connection_id++,message_queue);
					connections_.insert(std::make_pair(running_connection_id, connection_ptr));
					connection_ptr->run();
				}

			wait_for_connection();
			});
}



void MainServer::close() {
	try {
		for (auto &connection : connections_)
			connection.second->disconnect();
	}
	catch (...) {
		std::cout << "closing failed: connection already closed" << std::endl;
	}
}
