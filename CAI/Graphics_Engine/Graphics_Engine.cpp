#include "Graphics_Engine.h"

Graphics_Engine::Graphics_Engine()
{
	//_system_state_ = system_state::RUNNING;
	//window_ = std::make_shared<sf::RenderWindow>();
	//window_->create(sf::VideoMode(1920, 1080), "Agent Town", 3/*sf::Style::Resize*/);
	//loading_screen();
	//Quadtree_ = std::make_unique<QuadTree>(-1980, -1080, 1980, 1080);
	//window_->setActive(false);
}


//Graphics_Engine::Graphics_Engine(std::shared_ptr<QueueManager<message::message>> message_pipeline_)
//{
//	this->message_pipeline_ = message_pipeline_;
//	_system_state_ = RUNNING;
//	window_ = std::make_shared<sf::RenderWindow>();
//	window_->create(sf::VideoMode(1920, 1080), "Agent Town", 5/*sf::Style::Resize*/);
//	loading_screen();
//	Quadtree_ = std::make_unique<QuadTree>(-1980, -1080, 1980, 1080);
//	//Physics::GravityOn();
//	//window_->setFramerateLimit(60);
//	window_->setActive(false);
//}

void Graphics_Engine::operator=(const Graphics_Engine&& gm) noexcept
{
	//_system_state_ = gm._system_state_;
	//window_ = gm.window_;
	//loading_screen();
	//Quadtree_ = std::make_unique<QuadTree>( -1980, -1080, 1980, 1080);
	//window_->setActive(false);
}

void Graphics_Engine::loading_screen()
{
	std::shared_ptr<sf::Texture> loadingtxt = std::make_shared<sf::Texture>();
	if (!loadingtxt->loadFromFile("loading.png"))
		throw std::runtime_error("loading.png failed");
	Graphics loading(sf::Vector2f(0, 0), loadingtxt, window_);
	loading.Draw();
	window_->display();
}

void Graphics_Engine::run()
{
	//init
	BOOST_LOG_TRIVIAL(info) << "Graphics system is now running";
	_system_state_ = system_state::RUNNING;
	window_ = std::make_shared<sf::RenderWindow>();
	window_->create(sf::VideoMode(1920, 1080), "Agent Town", 3/*sf::Style::Resize*/);
	loading_screen();
	Quadtree_ = std::make_unique<QuadTree>(-1980, -1080, 1980, 1080);
	

	while (_system_state_ == system_state::PAUSED);
	if (_system_state_ == system_state::RUNNING) {
		//window_->setActive(true);

		object_vector_ = Factory::extract_object_list();

		while (window_->isOpen() && _system_state_ != system_state::TERMINATED)
		{
			game_loop();
		}
	}
}

void Graphics_Engine::game_loop()
{
	if (_system_state_ == system_state::RUNNING) {
		clean_dead_objects();
		activate_objects();
		objects_to_quadtree();
		draw_objects();
		event_loop();
	}
	while (_system_state_ == system_state::PAUSED);
		//add wait on lock, and notify on state change
}

void Graphics_Engine::clean_dead_objects()
{
	if(object_vector_->size() != 0)
		std::erase_if(*object_vector_, [](std::shared_ptr<Object> a) {return a->isUpForDestruction(); });
	/*if (agents_.size() != 0) {
		std::erase_if(agents_, [](std::pair<int, std::shared_ptr<Agent>> a) {return a.second->isUpForDestruction(); });
	}*/
}

void Graphics_Engine::activate_objects()
{
	for (int i = 0; i < object_vector_->size(); i++)
	{
		object_vector_->at(i)->action(); //check cooldown
	}
}

void Graphics_Engine::objects_to_quadtree()
{
	Quadtree_->CleanTree();
	for (short i = 0; i < object_vector_->size(); i++)
	{
		Quadtree_->insert(object_vector_->at(i).get());
	}
	Quadtree_->QueryNodes();
}

void Graphics_Engine::draw_objects()
{
	window_->clear();
	for (short i = 0; i < object_vector_->size(); i++)
	{
		object_vector_->at(i)->draw();
	}
	window_->display();
}

void Graphics_Engine::event_loop()
{
	while (window_->pollEvent(event_))
	{ 
		if (event_.type == sf::Event::Closed) {
			window_->close();
		}
		if (event_.type == sf::Event::KeyPressed) {
			if (event_.key.code == sf::Keyboard::Escape)
			{
				window_->close();
			}
		}
		if (event_.type == sf::Event::LostFocus)
		{

		}
		if (event_.type == sf::Event::GainedFocus)
		{

		}
	}
	while (incoming_messages_.size() > 0)
	{
		handle_messages();
	}

	if (_system_state_ == system_state::TERMINATED)
	{
	
	}
	else if (_system_state_ == system_state::PAUSED)
	{
	
	}
}

void Graphics_Engine::handle_messages()
{
	message::Parsed_Message msg = incoming_messages_.stop_until_pop();

	/*if (msg.type == "new")
	{
		create_new_agent(msg.new_id.value(), msg.connection_id);
	}
	else
	{
		if(msg.to)
			agents_.at(msg.to.value())->push_message(msg);
	}*/
}



//void Graphics_Engine::create_new_agent(int id,int connection_id)
//{
//	Factory::SetUpCar::new_SetUpCar(AABB(0, 0, 50, 115), 5, window_, id, connection_id);
//	if (agents_.count(id) == 0) {
//		agents_.emplace(std::pair(id, Factory::CreateCar()));
//		object_vector_->push_back(agents_.at(id));
//		agents_.at(id)->run();
//	}
//}

void Graphics_Engine::agent_added(std::shared_ptr<Agent> added_agent)
{
	auto position = added_agent->get_position();
	Factory::SetUpCar::new_SetUpCar(AABB(position.first, position.second, position.first +50, position.second+115), 5, window_, added_agent->get_agent_id());
	auto new_car = Factory::CreateCar();
	added_agent->subscribe(new_car);
	object_vector_->push_back(new_car);
}
void Graphics_Engine::agent_removed(std::shared_ptr<Agent> removed_agent)
{
	//removed Agent not object
	auto found = std::find_if(object_vector_->begin(), object_vector_->end(), [removed_agent](std::shared_ptr<Object>& a) {return a->get_id() == removed_agent->get_agent_id(); });
	(*found)->destroy();
}


Graphics_Engine::~Graphics_Engine()
{
}

void Graphics_Engine::provide_message(message::Parsed_Message &pmsg)
{
	incoming_messages_.push(pmsg);
}

std::string Graphics_Engine::component_name()
{
	return "graphics engine";
}


//add mutex lock to sync state change
void  Graphics_Engine::pause()
{
	_system_state_ = system_state::PAUSED;
}

void Graphics_Engine::restart()
{

}
void Graphics_Engine::close()
{
	this->_system_state_ = system_state::TERMINATED;
}

