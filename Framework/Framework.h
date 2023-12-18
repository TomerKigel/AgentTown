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

		enum class systems {Graphics, Interpreter, Communications, Representational_Network };


		//components api

		virtual void add_message_component(Component<message::Message>& component, bool needs_main_thread) {};

		virtual void add_parsed_message_component(Component<message::Message>& component, bool needs_main_thread) {};

		virtual void remove_component(std::string name) {};

		virtual void remove_component(Component<message::Message>& component) {};


		// representational network api

		/// <summary>
		/// creates a new representational network  <para />
		/// depends on the existence of a <see cref="Network_Representation"/> Component  <para />
		/// thus if an instance was not yet passed to Framework, the Framework will instantiate it automatically.
		/// </summary>
		/// <param name="network_name"> - The name of the new network to be created.  <para />
		/// defaults to 'DEFAULT' if no value is passed
		/// </param>
		virtual void create_network(std::string network_name = "DEFAULT") {};


		/// <summary>
		/// deletes an existing representational network  <para />
		/// </summary>
		/// <param name="network_name"> - The name of the network to be deleted.</param>
		/// <exception cref="std::runtime_error">- Thrown when invalid name is passed</exception> 
		virtual void delete_network(std::string network_name) {};


		// utility api

		virtual std::vector<std::string> get_names_of_components() {};

		//System state api

		void run(systems system);

		void halt_all();

		void halt(systems system);

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

		void start_all();
	};
}

