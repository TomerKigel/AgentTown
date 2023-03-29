#pragma once

#include "../Server_Communications/MainServer.h"
#include "../Message_System/message.h"
#include "../Graphics_Engine/GameEngine.h"
#include "../Message_System/QueueManager.h"
#include "../Framework/ConcreteMediator.h"
#include "../Message_Interpreting_System/Interpreter.h"

class Framework
{
private:
	std::unique_ptr<MainServer> base_server;

	boost::asio::io_context io_context_;
	GameEngine engine;
	std::thread context_thread, engine_thread, interpreter_thread;
	boost::asio::ip::tcp::endpoint end_point;
	Interpreter interpreter;
	std::unique_ptr<ConcreteMediator> SystemMediator;
	std::string host;
	int port;

	//std::shared_ptr<QueueManager<message::message>> message_pipeline_;
public:
	Framework();

	void start();

	void halt();

	void close();

	~Framework();
};

