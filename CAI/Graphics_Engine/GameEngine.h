#pragma once
#include <fstream>
#include <iterator>
#include "../Header_Files/APH.h"
#include <boost/lexical_cast.hpp>
#include "../Message_System/QueueManager.h"
#include "../Framework/Interfaces/interface_runnable.h"
#include "../Framework/Interfaces/Component.h"
#include "../AI_Elements/agent.h"
#include "../Network_Representation/Network.h"


class GameEngine : public interface_runnable , public Component<message::ParsedMessage>
{
private:
	Network<std::unique_ptr<agent>>* agent_network;

	enum engine_state_enum{RUNNING,PAUSED,TERMINATED};
	int engine_state_;

	std::shared_ptr<sf::RenderWindow> window_;
	sf::Event event_;
	std::unique_ptr<QuadTree> Quadtree_;
	std::unique_ptr<std::vector<std::shared_ptr<Object>>> object_vector_;
	QueueManager<message::ParsedMessage> incoming_messages;

	void event_loop();
	void handle_messages();
	void loading_screen();
	void activate_objects();
	void objects_to_quadtree();
	void draw_objects();
	void clean_dead_objects();
	void game_loop();

	//void create_new_agent(int id, int connection_id);
	void establish_network();
public:
	GameEngine(Network<std::unique_ptr<agent>>* network);
	GameEngine();
	~GameEngine();
	
	void operator=(const GameEngine&& gm);

	void provide_message(message::ParsedMessage &pmsg);

	void run();
	void pause();
	void restart();
	void quit();
};