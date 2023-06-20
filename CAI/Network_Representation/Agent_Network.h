#include "Network.h"
#include "../AI_Elements/agent.h"
#include "../Framework/Interfaces/Component.h"

class Agent_Network : public Network<std::unique_ptr<agent>>, public Component<message::ParsedMessage>, public interface_runnable
{
	bool alive;
	std::mutex alive_mutex;
	QueueManager<message::ParsedMessage> incoming_messages;
public:
	void add_node(int id, int connection)
	{
		nodes.push_back(std::make_unique<agent>(id, connection));
	}
	void remove_node(int id)
	{
		std::erase_if(nodes, [id](const std::unique_ptr<agent> &a) {return a->get_agent_id() == id; });
	}

	void add_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](const std::unique_ptr<agent>& a) {return a->get_agent_id() == agent_id; });
		if ((*found_agent)->get_agent_id() == agent_id)
			(*found_agent)->add_neighbour(neighbour_id);
	}

	void remove_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](const std::unique_ptr<agent>& a) {return a->get_agent_id() == agent_id; });
		if ((*found_agent)->get_agent_id() == agent_id)
			(*found_agent)->remove_neighbour(neighbour_id);
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
				if (iter->get()->get_agent_id() == msg.to.value())
					iter->get()->push_message(msg);
		}
		if (msg.new_id)
		{
			if (msg.connection_id) {
				add_node(msg.new_id.value(), msg.connection_id);
			}
		}
	}

};