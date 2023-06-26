#include "Network.h"
#include "../AI_Elements/agent.h"
#include "../Framework/Interfaces/Component.h"
#include "../AI_Elements/Interfaces/NetworkObserver.h"

class Agent_Network : public Network<std::unique_ptr<agent>>, public Component<message::ParsedMessage>, public interface_runnable
{
	bool alive;
	std::mutex alive_mutex;
	QueueManager<message::ParsedMessage> incoming_messages;
	std::vector<NetworkObserver&> network_observers;
public:
	void add_node(int id, int connection)
	{
		nodes.insert(std::make_pair(id, std::make_unique<agent>(id, connection)));
	}
	void remove_node(int id)
	{
		std::erase_if(nodes, [id](const std::unique_ptr<agent> &a) {return a->get_agent_id() == id; });
	}

	void add_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](const std::unique_ptr<agent>& a) {return a->get_agent_id() == agent_id; });
		if ((*found_agent).second->get_agent_id() == agent_id)
			(*found_agent).second->add_neighbour(neighbour_id);
	}

	void remove_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](const std::unique_ptr<agent>& a) {return a->get_agent_id() == agent_id; });
		if ((*found_agent).second->get_agent_id() == agent_id)
			(*found_agent).second->remove_neighbour(neighbour_id);
	}

	virtual void provide_message(message::ParsedMessage& msg)
	{
		incoming_messages.push(msg);
	}
	
	void subscribe_to_agent(int agent_id,std::shared_ptr<GraphicsObserver> observer)
	{
		nodes.at(agent_id)->subscribe(observer);
	}

	void unsubscribe_from_agent(int agent_id, std::shared_ptr<GraphicsObserver> observer)
	{
		nodes.at(agent_id)->unsubscribe(observer);
	}

	void subscribe_to_network(NetworkObserver &observer)
	{
		network_observers.push_back(observer);
	}

	void unsubscribe_from_network(NetworkObserver& observer)
	{
		std::remove_if(network_observers.begin(), network_observers.end(), [observer](NetworkObserver& a) {return a == observer; });
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
			if (msg.connection_id) {
				add_node(msg.new_id.value(), msg.connection_id);
			}
		}
	}
};