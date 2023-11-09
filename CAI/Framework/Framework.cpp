#include "Framework.h"
//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/basic_file_sink.h"
#include "Interfaces/Component.h"
using namespace cai;

Framework::Framework()
{
	//auto sharedFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt");
	//auto framework_logger = std::make_shared<spdlog::logger>("main_logger", sharedFileSink);
	//spdlog::set_default_logger(framework_logger);
	//spdlog::info("Framework initializing");
    host_ = "127.0.0.1";
	port_ = 7777;
	end_point_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host_), port_);
	base_server_ = std::make_unique<MainServer>(io_context_, end_point_);
	base_server_->run();
	engine_ = Graphics_Engine();
	agent_network_.subscribe_to_network(&engine_);
	std::initializer_list<Component<message::Message>*> msg_based = { &*base_server_, &interpreter_ } ;
	std::initializer_list<Component<message::Parsed_Message>*> pmsg_based = { &agent_network_, &engine_ };
	SystemMediator_ = std::make_unique<Concrete_Mediator>(msg_based, pmsg_based);
	//spdlog::info("Framework initialized successfully");
	start_all();
}

void Framework::start_all()
{
	context_thread_ = std::thread([this]() { io_context_.run(); });
	interpreter_thread_ = std::thread([this]() { interpreter_.run(); });
	representational_network_thread_ = std::thread([this]() { agent_network_.run(); });
	engine_.run();
}

void Framework::run(systems system)
{
	switch (system) {
	case systems::Communications:
		if (base_server_.get()->state() == system_state::PAUSED) {
			base_server_.get()->run();
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

void cai::Framework::halt(systems system)
{
	switch (system) {
	case systems::Communications:
		if (base_server_.get()->state() == system_state::RUNNING ) {
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
	//spdlog::info("Framework terminated");
}

Framework::~Framework()
{
	context_thread_.join();
	interpreter_thread_.join();
	representational_network_thread_.join();
}
