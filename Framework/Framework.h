#pragma once

#include "MainServer.h"
#include "message.h"
#include "Graphics_Engine/Graphics_Engine.h"
#include "Queue_Manager.h"
#include "Concrete_Mediator.h"
#include "Interpreter.h"
#include "Agent_Network.h"
#include "Interface_Framework.h"

namespace cai
{
	class Framework : public Interface_Framework
	{
	public:
		Framework();

		Framework(const Framework&) = delete;


		//components api

		void add_system(systems system);

		void remove_system(systems system);

		// representational network api

		/// <summary>
		/// creates a new representational network  <para />
		/// depends on the existence of a <see cref="Network_Representation"/> Component  <para />
		/// thus if an instance was not yet passed to Framework, the Framework will instantiate it automatically.
		/// </summary>
		/// <param name="network_name"> - The name of the new network to be created.  <para />
		/// defaults to 'DEFAULT' if no value is passed
		/// </param>
		void create_network(std::string network_name = "DEFAULT");


		/// <summary>
		/// deletes an existing representational network  <para />
		/// </summary>
		/// <param name="network_name"> - The name of the network to be deleted.</param>
		/// <exception cref="std::runtime_error">- Thrown when invalid name is passed</exception> 
		void delete_network(std::string network_name);


		// utility api

		std::vector<std::string> get_names_of_components();

		//System state api

		void run(systems system);

		void halt(systems system);

		void run_all();

		void halt_all();

		void close() noexcept;

		~Framework();

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
	};
}

