#pragma once

#include "MainServer.h"
#include "message.h"
#include "Graphics_Engine/Graphics_Engine.h"
#include "Queue_Manager.h"
#include "Concrete_Mediator.h"
#include "Interpreter.h"
#include "Agent_Network.h"

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

		void start_all();

	public:
		Framework();

		Framework(const Framework&) = delete;

		enum class systems { Graphics, Interpreter, Communications, Representational_Network };

		void run(systems system);

		void halt_all();

		void halt(systems system);

		void close() noexcept;

		~Framework();
	};
}

