#pragma once
#include <string>
#include <vector>
#include "Component.h"




class Interface_Framework
{
public:
	//components api

	enum class systems { Graphics, Interpreter, Communications, Representational_Network };

	virtual void add_system(systems system) = 0;

	virtual void remove_system(systems system) = 0;

	// representational network api

	virtual void create_network(std::string network_name = "DEFAULT") = 0;

	virtual void delete_network(std::string network_name) = 0;


	// utility api

	virtual std::vector<std::string> get_names_of_components() = 0;


	// system state api

	virtual void run(systems system) = 0;

	virtual void halt(systems system) = 0;

	virtual void run_all() = 0;

	virtual void halt_all() = 0;

	virtual void close() noexcept = 0;
};