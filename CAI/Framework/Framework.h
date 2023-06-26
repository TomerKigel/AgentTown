#pragma once

#include "../Server_Communications/MainServer.h"
#include "../Message_System/message.h"
#include "../Graphics_Engine/GameEngine.h"
#include "../Message_System/QueueManager.h"
#include "../Framework/ConcreteMediator.h"
#include "../Message_Interpreting_System/Interpreter.h"
#include "../Network_Representation/Agent_Network.h"
class Framework
{
private:
	std::unique_ptr<MainServer> base_server;
	GameEngine engine;
	Interpreter interpreter;
	Agent_Network agent_network;

	boost::asio::io_context io_context_;
	boost::asio::ip::tcp::endpoint end_point;
	std::string host;
	int port;

	std::thread context_thread, engine_thread, interpreter_thread, representational_network_thread;
	std::unique_ptr<ConcreteMediator> SystemMediator;
	
public:
	Framework();

	void start();

	void halt();

	void close();

	~Framework();
};

