/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/

#define BOOST_ALL_DYN_LINK

#include "Framework.h"
#include "Component.h"
#include "Debug.h"

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

using namespace cai;

namespace keywords = boost::log::keywords;
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

void Framework::init_logging_() {
	logging::add_file_log(
		"log.txt",  // File name_
		keywords::format = "[%TimeStamp%] [%Severity%]: %Message%"
	);
	logging::add_common_attributes();
}

Framework::Framework()
{
	//set network parameters
	host_ = "127.0.0.1";
	port_ = 7777;

	//logging starts
	init_logging_();
	BOOST_LOG_TRIVIAL(info) << "Framework is initialized with:\tport:" << port_ << "\tip:" << host_;
	

	//add mandatory systems
	SystemMediator_.add_component(&interpreter_);
	SystemMediator_.add_component(&networks_manager_);

	//set mandatory systems as active
	map_of_active_components_.insert(std::make_pair(systems::Interpreter, activity::Active));
	map_of_active_components_.insert(std::make_pair(systems::Representational_Network, activity::Active));
}

void Framework::run_all()
{
	//run mandatory systems
	interpreter_thread_ = std::thread([this]() { interpreter_.run(); });
	representational_network_thread_ = std::thread([this]() { networks_manager_.run_all(); });


	//run optional systems
	if (map_of_active_components_.count(systems::Communications) == 1 && map_of_active_components_.at(systems::Communications) == activity::Active){
		base_server_.run();
		//context_thread_ = std::thread([this]() { io_context_.run(); });
	}
	
	
	if(map_of_active_components_.count(systems::Graphics) == 1 && map_of_active_components_.at(systems::Graphics) == activity::Active) {
		engine_.run(); // blocking system because of sfml. keep at the end of the code block as long as sfml is used.
	}
}

void Framework::run(systems system)
{
	switch (systems::Communications) {
	case systems::Communications:
		if (base_server_.state() == system_state::PAUSED) {
			base_server_.run();
		}
		break;
	case systems::Interpreter:
		if (interpreter_.state() == system_state::PAUSED) {
			interpreter_.run();
		}
		break;
	case systems::Representational_Network:
		if (networks_manager_.state() == system_state::PAUSED) {
			networks_manager_.run_all();
		}
		break;
	case systems::Graphics:
		if (engine_.state() == system_state::PAUSED) {
			engine_.run(); // blocking system because of sfml. keep at the end of the code block as long as sfml is used.
		}
		break;
	default:
		throw std::runtime_error("Error: attempt to start a system that doesn't exist");
	}
}

void Framework::pause_all()
{
	interpreter_.pause();
	networks_manager_.pause_all();
	engine_.pause();
	base_server_.pause();
}

void Framework::pause(systems system)
{
	switch (system) {
	case systems::Communications:
		if (base_server_.state() == system_state::RUNNING) {
			base_server_.pause();
		}
		break;
	case systems::Interpreter:
		if (interpreter_.state() == system_state::RUNNING) {
			interpreter_.pause();
		}
		break;
	case systems::Representational_Network:
		if (networks_manager_.state() == system_state::RUNNING) {
			networks_manager_.pause_all();
		}
		break;
	case systems::Graphics:
		if (engine_.state() == system_state::RUNNING) {
			engine_.pause();
		}
		break;
	default:
		throw std::runtime_error("Error: attempt to start a system that doesn't exist");
	}
}

void Framework::close() noexcept
{
	networks_manager_.pause_all();
	interpreter_.pause();
	SystemMediator_.remove_component(&networks_manager_);


	engine_.close();
	base_server_.close();
	map_of_active_components_.at(systems::Graphics) = activity::InActive;
	map_of_active_components_.at(systems::Communications) = activity::InActive;
}

Framework::~Framework()
{
	interpreter_thread_.join();
	representational_network_thread_.join();
	logging::core::get()->flush();
}

void Framework::add_system(systems system)
{
	switch (system)
	{
	case systems::Graphics:
		if (map_of_active_components_.count(systems::Graphics) == 0 || map_of_active_components_.at(systems::Graphics) == activity::InActive){
			engine_ = Graphics_Engine();
			SystemMediator_.add_component(&engine_);
			networks_manager_.subscribe_to_network(&engine_);
			map_of_active_components_.insert(std::make_pair(systems::Graphics, activity::Active));
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << "no system added, already exists";
		}
		break;
	case systems::Interpreter:
		//log - no system added
		break;
	case systems::Communications:
		if (map_of_active_components_.count(systems::Communications) == 0 || map_of_active_components_.at(systems::Communications) == activity::InActive) {
			base_server_.bind_server(host_,port_);
			SystemMediator_.add_component(&base_server_);
			map_of_active_components_.insert(std::make_pair(systems::Communications, activity::Active));
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << "no system added, already exists";
		}
		break;
	case systems::Representational_Network:
		BOOST_LOG_TRIVIAL(warning) << "no system added";
		break;
	}
}

void Framework::remove_system(systems system)
{
	switch (system)
	{
	case systems::Graphics:
		if (map_of_active_components_.count(systems::Graphics) == 1 && map_of_active_components_.at(systems::Graphics) == activity::Active) {
			SystemMediator_.remove_component(&engine_);
			networks_manager_.unsubscribe_from_network(&engine_);
		}
		break;
	case systems::Interpreter:
		BOOST_LOG_TRIVIAL(warning) << "can't remove interpreter";
		break;
	case systems::Communications:
		if (map_of_active_components_.count(systems::Communications) == 1 && map_of_active_components_.at(systems::Communications) == activity::Active) {
			SystemMediator_.remove_component(&base_server_);
		}
		break;
	case systems::Representational_Network:
		BOOST_LOG_TRIVIAL(warning) << "can't remove Representational_Network";
		break;
	}
}

void Framework::create_network(std::string network_name)
{
	networks_manager_.create_network(network_name);
}

void Framework::delete_network(std::string network_name) 
{ 
	networks_manager_.delete_network(network_name);
};

std::vector<std::string> Framework::get_names_of_components()
{
	return SystemMediator_.get_component_names();
}
