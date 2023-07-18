#pragma once

#include "../Server_Communications/MainServer.h"
#include "../Message_System/message.h"
#include "../Graphics_Engine/Graphics_Engine.h"
#include "../Message_System/Queue_Manager.h"
#include "../Framework/Concrete_Mediator.h"
#include "../Message_Interpreting_System/Interpreter.h"
#include "../Network_Representation/Agent_Network.h"

namespace cai
{
	class Framework
	{
	private:
		std::unique_ptr<MainServer> base_server_;
		Graphics_Engine engine_;
		Interpreter interpreter_;
		Agent_Network agent_network_;

		boost::asio::io_context io_context_;
		boost::asio::ip::tcp::endpoint end_point_;
		std::string host_;
		int port_;

		std::thread context_thread_, engine_thread_, interpreter_thread_, representational_network_thread_;
		std::unique_ptr<Concrete_Mediator> SystemMediator_;

	public:
		Framework();

		Framework(const Framework&) = delete;

		void start();

		void halt();

		void close();

		~Framework();
	};
}

