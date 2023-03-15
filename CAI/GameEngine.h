#pragma once
#include "Sound.h"
#include "Graphics.h"
#include "QuadTree.h"
#include <fstream>
#include <iterator>
#include "Interactable.h"
#include "Object.h"
#include "APH.h"
#include "ThreadSafeQueue.h"
#include <boost/lexical_cast.hpp>

#include <cmath>
#include <matplot/matplot.h>


class GameEngine
{
private:
	enum engine_state_enum{RUNNING,PAUSED,TERMINATED};
	int engine_state;

	std::shared_ptr<sf::RenderWindow> window_;
	sf::Event event;
	std::shared_ptr<ThreadSafeQueue<message::message>> message_queue_;
	std::unique_ptr<QuadTree> Quadtree_;
	std::unique_ptr<std::vector<std::shared_ptr<Object>>> object_vector;
	std::map<int,std::shared_ptr<agent>> agents;

	void event_loop();
	void handle_messages();
	void handle_new_agent_message(message::message& msg);
	void handle_message_to_existing_agent(message::message& msg);
	void loading_screen();
	void activate_objects();
	void objects_to_quadtree();
	void draw_objects();
	void clean_dead_objects();
	void game_loop();
public:
	GameEngine();
	GameEngine(std::shared_ptr<ThreadSafeQueue<message::message>> &message_queue);
	~GameEngine();
	
	void operator=(const GameEngine&& gm);

	void run();
	void pause();
	std::string statistics();
	void restart();
	void quit();
};