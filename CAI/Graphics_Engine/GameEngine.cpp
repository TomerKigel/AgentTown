#include "GameEngine.h"

GameEngine::GameEngine()
{
	engine_state_ = RUNNING;
	window_ = std::make_shared<sf::RenderWindow>();
	window_->create(sf::VideoMode(1920, 1080), "Agent Town", 3/*sf::Style::Resize*/);
	loading_screen();
	Quadtree_ = std::make_unique<QuadTree>(-1980, -1080, 1980, 1080);
	window_->setActive(false);
}

//GameEngine::GameEngine(std::shared_ptr<QueueManager<message::message>> message_pipeline_)
//{
//	this->message_pipeline_ = message_pipeline_;
//	engine_state_ = RUNNING;
//	window_ = std::make_shared<sf::RenderWindow>();
//	window_->create(sf::VideoMode(1920, 1080), "Agent Town", 5/*sf::Style::Resize*/);
//	loading_screen();
//	Quadtree_ = std::make_unique<QuadTree>(-1980, -1080, 1980, 1080);
//	//Physics::GravityOn();
//	//window_->setFramerateLimit(60);
//	window_->setActive(false);
//}

void GameEngine::operator=(const GameEngine&& gm)
{
	engine_state_ = gm.engine_state_;
	window_ = gm.window_;
	loading_screen();
	Quadtree_ = std::make_unique<QuadTree>( -1980, -1080, 1980, 1080);
	window_->setActive(false);
}

void GameEngine::loading_screen()
{
	std::shared_ptr<sf::Texture> loadingtxt = std::make_shared<sf::Texture>();
	if (!loadingtxt->loadFromFile("loading.png"))
		throw("loading");
	Graphics loading(sf::Vector2f(0, 0), loadingtxt, window_);
	loading.Draw();
	window_->display();
}

void GameEngine::run()
{
	window_->setActive(true);
	
	
	object_vector_ = Factory::extract_object_list();

	
	
	while (window_->isOpen())
	{ 
		game_loop();
	}
}

void GameEngine::game_loop()
{
	if (engine_state_ == RUNNING) {
		clean_dead_objects();
		activate_objects();
		objects_to_quadtree();
		draw_objects();
		event_loop();
	}
}

void GameEngine::clean_dead_objects()
{
	/*for (short i = 0; i < object_vector_->size(); i++)
	{
		bool ti = object_vector_->at(i)->isUpForDestruction();
		if (ti) {
			object_vector_->erase(object_vector_->begin() + i);
			object_vector_->shrink_to_fit();
		}
	}*/
	if(object_vector_->size() != 0)
		std::erase_if(*object_vector_, [](std::shared_ptr<Object> a) {return a->isUpForDestruction(); });
	if (agents_.size() != 0) {
		std::erase_if(agents_, [](std::pair<int, std::shared_ptr<agent>> a) {return a.second->isUpForDestruction(); });
	}
}

void GameEngine::activate_objects()
{
	for (int i = 0; i < object_vector_->size(); i++)
	{
		object_vector_->at(i)->action(); //check cooldown
	}
}

void GameEngine::objects_to_quadtree()
{
	Quadtree_->CleanTree();
	for (short i = 0; i < object_vector_->size(); i++)
	{
		Quadtree_->insert(object_vector_->at(i).get());
	}
	Quadtree_->QueryNodes();
}

void GameEngine::draw_objects()
{
	window_->clear();
	for (short i = 0; i < object_vector_->size(); i++)
	{
		object_vector_->at(i)->draw();
	}
	window_->display();
}

void GameEngine::event_loop()
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
	while (incoming_messages.size() > 0)
	{
		handle_messages();
	}

	if (engine_state_ == TERMINATED)
	{
	
	}
	else if (engine_state_ == PAUSED)
	{
	
	}
}

void GameEngine::handle_messages()
{
	message::ParsedMessage msg = incoming_messages.stop_until_pop();

	if (msg.type == "new")
	{
		create_new_agent(msg.new_id.value(), msg.connection_id);
	}
	else
	{
		if(msg.to)
			agents_.at(msg.to.value())->push_message(msg);
	}
}



void GameEngine::create_new_agent(int id,int connection_id)
{
	Factory::SetUpCar::new_SetUpCar(AABB(0, 0, 50, 115), 5, window_, id, connection_id);
	if (agents_.count(id) == 0) {
		agents_.emplace(std::pair(id, Factory::CreateCar()));
		object_vector_->push_back(agents_.at(id));
		agents_.at(id)->run();
	}
}

GameEngine::~GameEngine()
{
}



void GameEngine::provide_message(message::ParsedMessage &pmsg)
{
	incoming_messages.push(pmsg);
}

void  GameEngine::pause()
{

}
std::string GameEngine::statistics()
{
	return "";
}
void GameEngine::restart()
{

}
void GameEngine::quit()
{

}