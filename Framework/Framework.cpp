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


#include "Framework.h"
#include "Component.h"

using namespace cai;

Framework::Framework()
{
	//set network parameters
	host_ = "127.0.0.1";
	port_ = 7777;

	//add mandatory systems
	SystemMediator_ = std::make_unique<Concrete_Mediator>();
	SystemMediator_->add_component(&interpreter_);
	SystemMediator_->add_component(&networks_manager_);

	//set mandatory systems as active
	list_of_active_components.push_back(&interpreter_);
	list_of_active_components.push_back(&networks_manager_);
}

void Framework::run_all()
{
	//run mandatory systems
	interpreter_thread_ = std::thread([this]() { interpreter_.run(); });
	representational_network_thread_ = std::thread([this]() { networks_manager_.run_all(); });


	//run optional systems
	if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &*base_server_) != list_of_active_components.end()) {
		base_server_->run();
		context_thread_ = std::thread([this]() { io_context_.run(); });
	}
	
	
	if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &engine_) != list_of_active_components.end()) {
		engine_.run(); // blocking system because of sfml. keep at the end of the code block as long as sfml is used.
	}
}

void Framework::run(systems system)
{
	switch (systems::Communications) {
	case systems::Communications:
		if (base_server_->state() == system_state::PAUSED) {
			base_server_->run();
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
		throw "Error: attempt to start a system that doesn't exist";
	}
}

void Framework::halt_all()
{
	interpreter_.pause();
	networks_manager_.pause_all();
	engine_.pause();
	base_server_.get()->pause();
}

void Framework::halt(systems system)
{
	switch (system) {
	case systems::Communications:
		if (base_server_.get()->state() == system_state::RUNNING) {
			base_server_.get()->pause();
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
		throw "Error: attempt to start a system that doesn't exist";
	}
}

void Framework::close() noexcept
{
	networks_manager_.close_all();
	interpreter_.close();
	engine_.close();
	base_server_->close();
}

Framework::~Framework()
{
	context_thread_.join();
	interpreter_thread_.join();
	representational_network_thread_.join();
}

void Framework::add_system(systems system)
{
	switch (system)
	{
	case systems::Graphics:
		if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &engine_) == list_of_active_components.end()){
			engine_ = Graphics_Engine();
			SystemMediator_->add_component(&engine_);
			networks_manager_.subscribe_to_network(&engine_);
			list_of_active_components.push_back(&engine_);
		}
		else
		{
			//log no system added, already exists
		}
		break;
	case systems::Interpreter:
		//log no system added
		break;
	case systems::Communications:
		if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &*base_server_) == list_of_active_components.end()) {
			end_point_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host_), port_);
			base_server_ = std::make_unique<MainServer>(io_context_, end_point_);
			SystemMediator_->add_component(&*base_server_);
			list_of_active_components.push_back(&*base_server_);
		}
		else
		{
			//log no system added, already exists
		}
		break;
	case systems::Representational_Network:
		//log no system added
		break;
	}
}

void Framework::remove_system(systems system)
{
	switch (system)
	{
	case systems::Graphics:
		if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &engine_) != list_of_active_components.end()) {
			SystemMediator_->remove_component(&engine_);
			networks_manager_.unsubscribe_from_network(&engine_);
		}
		break;
	case systems::Interpreter:
		//log can't remove interpreter
		break;
	case systems::Communications:
		if (std::find(list_of_active_components.begin(), list_of_active_components.end(), &*base_server_) != list_of_active_components.end()) {
			SystemMediator_->remove_component(&*base_server_);
		}
		break;
	case systems::Representational_Network:
		//log can't remove Representational_Network
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
	std::vector<std::string> component_names;
	for (Component* component : list_of_active_components)
	{
		component_names.push_back(component->component_name());
	}
	return component_names;
}