#pragma once
#include <fstream>
#include <iterator>
#include "../Header_Files/APH.h"
#include <boost/lexical_cast.hpp>
#include "../Message_System/Queue_Manager.h"
#include "../Framework/Interfaces/Interface_Runnable.h"
#include "../Framework/Interfaces/Component.h"
#include "../AI_Elements/Agent.h"
#include "../Network_Representation/Agent_Network.h"
#include "../AI_Elements/Interfaces/Interface_Network_Observer.h"

class Graphics_Engine : public Interface_Runnable , public Component<message::Parsed_Message> , public Interface_Network_Observer
{
private:
	std::shared_ptr<sf::RenderWindow> window_;
	sf::Event event_;
	std::unique_ptr<QuadTree> Quadtree_;
	std::unique_ptr<std::vector<std::shared_ptr<Object>>> object_vector_;
	Queue_Manager<message::Parsed_Message> incoming_messages_;

	void event_loop();
	void handle_messages();
	void loading_screen();
	void activate_objects();
	void objects_to_quadtree();
	void draw_objects();
	void clean_dead_objects();
	void game_loop();

public:

	Graphics_Engine();
	~Graphics_Engine();
	
	void operator=(const Graphics_Engine&& gm) noexcept;

	void provide_message(message::Parsed_Message &pmsg);
	std::string service_name();

	void agent_added(std::shared_ptr<Agent> added_agent);
	void agent_removed(std::shared_ptr<Agent> added_agent);


	void run();
	void pause();
	void restart();
	void close();

};