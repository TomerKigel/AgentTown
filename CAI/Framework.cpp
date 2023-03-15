#include "Framework.h"

Framework::Framework()
{
    host = "127.0.0.1";
	port = 7777;
	end_point = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
	Queue = std::make_shared<ThreadSafeQueue<message::message>>();
	base_server = std::make_unique<MainServer>(io_context_, end_point,Queue);
	base_server->start();
	context_thread = std::thread([this](){ io_context_.run(); });
	engine = GameEngine(Queue);
	//engine_thread = std::thread([this]() { engine.run(); });
	engine.run();
}

Framework::~Framework()
{
	context_thread.join();
}