#include "Framework.h"

Framework::Framework()
{
    host = "127.0.0.1";
	port = 7777;
	end_point = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host), port);
	base_server = std::make_unique<MainServer>(io_context_, end_point);
	base_server->start();
	engine = GameEngine();
	SystemMediator = std::make_unique<ConcreteMediator>(&engine, &*base_server, &interpreter);
}

void Framework::start()
{
	context_thread = std::thread([this]() { io_context_.run(); });
	interpreter_thread = std::thread([this]() { interpreter.ResponseLoop(); });
	engine.run();
}

void Framework::halt()
{

}

void Framework::close()
{
	interpreter.kill();
	engine.quit();
	base_server->close();
}

Framework::~Framework()
{
	context_thread.join();
	interpreter.kill();
	interpreter_thread.join();
}