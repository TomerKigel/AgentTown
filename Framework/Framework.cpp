#include "Framework.h"
#include "Component.h"
using namespace cai;

Framework::Framework()
{
	host_ = "127.0.0.1";
	port_ = 7777;
	std::initializer_list<Component<message::Message>*> msg_based = { /*&*base_server_,*/ &interpreter_};
	std::initializer_list<Component<message::Parsed_Message>*> pmsg_based = { &agent_network_/*, &engine_*/};
	SystemMediator_ = std::make_unique<Concrete_Mediator>(msg_based, pmsg_based);
	list_of_active_components.push_back(&interpreter_);
	list_of_active_components.push_back(&agent_network_);
}

void Framework::run_all()
{
	//mandatory systems
	interpreter_thread_ = std::thread([this]() { interpreter_.run(); });
	representational_network_thread_ = std::thread([this]() { agent_network_.run(); });


	//optional systems
	base_server_->run();
	context_thread_ = std::thread([this]() { io_context_.run(); });
	
	//blocking system because of sfml
	engine_.run();
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
		if (agent_network_.state() == system_state::PAUSED) {
			agent_network_.run();
		}
		break;
	case systems::Graphics:
		if (engine_.state() == system_state::PAUSED) {
			engine_.run();
		}
		break;
	default:
		throw "Error: attempt to start a system that doesn't exist";
	}
}

void Framework::halt_all()
{
	interpreter_.pause();
	agent_network_.pause();
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
		if (agent_network_.state() == system_state::RUNNING) {
			agent_network_.pause();
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
	agent_network_.close();
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
		engine_ = Graphics_Engine();
		SystemMediator_->add_component(&engine_);
		agent_network_.subscribe_to_network(&engine_);
		list_of_active_components.push_back(&engine_);
		break;
	case systems::Interpreter:
		SystemMediator_->add_component(&interpreter_);
		break;
	case systems::Communications:
		end_point_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host_), port_);
		base_server_ = std::make_unique<MainServer>(io_context_, end_point_);
		SystemMediator_->add_component(&*base_server_);
		list_of_active_components.push_back(&*base_server_);
		break;
	case systems::Representational_Network:
		SystemMediator_->add_component(&agent_network_);
		break;
	}
}

void Framework::remove_system(systems system)
{
	switch (system)
	{
	case systems::Graphics:
		SystemMediator_->remove_component(&engine_);
		agent_network_.unsubscribe_from_network(&engine_);
		break;
	case systems::Interpreter:
		//can't remove interpreter
		break;
	case systems::Communications:
		SystemMediator_->remove_component(&*base_server_);
		break;
	case systems::Representational_Network:
		//can't remove Representational_Network
		break;
	}
}

void Framework::create_network(std::string network_name)
{
	
}

void Framework::delete_network(std::string network_name) 
{ 

};

std::vector<std::string> Framework::get_names_of_components()
{
	std::vector<std::string> a;
	return a;
}