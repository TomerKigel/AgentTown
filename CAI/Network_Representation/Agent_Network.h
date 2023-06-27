#pragma once
#include "Network.h"
#include "../AI_Elements/agent.h"
#include "../Framework/Interfaces/Component.h"


class Agent_Network : public Network<std::shared_ptr<agent>>, public Component<message::ParsedMessage>, public interface_runnable
{
	bool alive;
	std::mutex alive_mutex;
	QueueManager<message::ParsedMessage> incoming_messages;
public:

	Agent_Network()
	{
		alive = true;
	}
	void add_node(int id, int connection)
	{
		nodes.insert(std::make_pair(id, std::make_shared<agent>(id, connection)));
		nodes.at(id)->run();
		for (auto iter = network_observers.begin(); iter != network_observers.end(); iter++)
		{
			(*iter)->agent_added(nodes.at(id));
		}
	}
	void remove_node(int id)
	{
		if (nodes.count(id) != 0){
			for (auto iter = network_observers.begin(); iter != network_observers.end(); iter++)
			{
				(*iter)->agent_removed(nodes.at(id));
			}
			std::erase_if(nodes, [id](std::pair<int, std::shared_ptr<agent>> a) {return a.first == id; });
		}
	}

	void add_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](std::pair<int, std::shared_ptr<agent>> a) {return a.first == agent_id; });
		if ((*found_agent).second->get_agent_id() == agent_id)
			(*found_agent).second->add_neighbour(neighbour_id);
	}

	void remove_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](std::pair<int, std::shared_ptr<agent>> a) {return a.first == agent_id; });
		if ((*found_agent).second->get_agent_id() == agent_id)
			(*found_agent).second->remove_neighbour(neighbour_id);
	}

	
	
	void subscribe_to_agent(int agent_id,std::shared_ptr<GraphicsObserver> observer)
	{
		nodes.at(agent_id)->subscribe(observer);
	}

	void unsubscribe_from_agent(int agent_id, std::shared_ptr<GraphicsObserver> observer)
	{
		nodes.at(agent_id)->unsubscribe(observer);
	}


	virtual void provide_message(message::ParsedMessage& msg)
	{
		incoming_messages.push(msg);
	}

	void run()
	{
		std::unique_lock lock(alive_mutex);

		message::ParsedMessage msg = incoming_messages.stop_until_pop();
		if (msg.to) {
			for (auto iter = nodes.begin(); iter != nodes.end(); iter++)
				if (iter->second->get_agent_id() == msg.to.value())
					iter->second->push_message(msg);
		}
		if (msg.new_id)
		{
			add_node(msg.new_id.value(), msg.connection_id);
			nodes.at(msg.new_id.value())->update_position(std::make_pair(msg.x_position.value(), msg.y_position.value()));

		}

		if (alive) {
			lock.unlock();
			run();
		}
		else
			lock.unlock();
	}
};