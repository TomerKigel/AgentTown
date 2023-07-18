#include "Framework.h"
using namespace cai;

Framework::Framework()
{
    host_ = "127.0.0.1";
	port_ = 7777;
	end_point_ = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(host_), port_);
	base_server_ = std::make_unique<MainServer>(io_context_, end_point_);
	base_server_->start();
	engine_ = Graphics_Engine();
	agent_network_.subscribe_to_network(&engine_);
	std::initializer_list<Component<message::Message>*> msg_based = { &*base_server_, &interpreter_ } ;
	std::initializer_list<Component<message::Parsed_Message>*> pmsg_based = { &agent_network_, &engine_ };
	SystemMediator_ = std::make_unique<Concrete_Mediator>(msg_based, pmsg_based);
}

void Framework::start()
{
	context_thread_ = std::thread([this]() { io_context_.run(); });
	interpreter_thread_ = std::thread([this]() { interpreter_.run(); });
	representational_network_thread_ = std::thread([this]() { agent_network_.run(); });
	engine_.run();
	
}

void Framework::halt()
{
	io_context_.stop();
	interpreter_.pause();
	agent_network_.pause();
	engine_.pause();
	base_server_.get()->pause();
}

void Framework::close()
{
	interpreter_.kill();
	engine_.quit();
	base_server_->close();
}

Framework::~Framework()
{
	context_thread_.join();
	interpreter_thread_.join();
	representational_network_thread_.join();
}
