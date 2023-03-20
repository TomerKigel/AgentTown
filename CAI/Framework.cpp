#include "Framework.h"

Framework::Framework()
{
    host = "127.0.0.1";
	port = 7777;
	end_point = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
	message_pipeline_ = std::make_shared<QueueManager<message::message>>();
	base_server = std::make_unique<MainServer>(io_context_, end_point, message_pipeline_);
	base_server->start();
	context_thread = std::thread([this](){ io_context_.run(); });
	engine = GameEngine(message_pipeline_);
	//engine_thread = std::thread([this]() { engine.run(); });
	engine.run();
}

Framework::~Framework()
{
	context_thread.join();
}