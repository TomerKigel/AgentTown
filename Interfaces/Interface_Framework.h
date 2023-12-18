#pragma once
#include <string>
#include <vector>
#include "Component.h"

enum class systems;


class Interface_Framework
{
	//components api

	virtual void add_message_component(Component<message::Message> &component,bool needs_main_thread) = 0;

	virtual void add_parsed_message_component(Component<message::Message> &component, bool needs_main_thread) = 0;

	virtual void remove_component(std::string name) = 0;

	virtual void remove_component(Component<message::Message> &component) = 0;


	// representational network api

	virtual void create_network(std::string network_name = "DEFAULT") = 0;

	virtual void delete_network(std::string network_name) = 0;


	// utility api

	virtual std::vector<std::string> get_names_of_components() = 0;



	// system state api

	virtual void run(systems system);

	virtual void halt(systems system);

	virtual void run_all();

	virtual void halt_all();

	virtual void close() noexcept;
};