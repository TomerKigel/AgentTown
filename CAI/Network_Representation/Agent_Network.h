#include "Network.h"
#include "../AI_Elements/agent.h"

class Agent_Network : public Network<agent>
{
	void add_node(int id, int connection)
	{
		nodes.emplace_back(id, connection);
	}
	void remove_node(int id)
	{
		std::erase_if(nodes, [id](std::shared_ptr<agent> a) {return a.get()->get_agent_id() == id; });
	}

	void add_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](std::shared_ptr<agent> a) {return a.get()->get_agent_id() == agent_id; });
		if ((*found_agent).get_agent_id() == agent_id)
			(*found_agent).add_neighbour(neighbour_id);
	}

	void remove_neighbour_to_agent(int agent_id, int neighbour_id)
	{
		auto found_agent = std::find_if(nodes.begin(), nodes.end(), [agent_id](std::shared_ptr<agent> a) {return a.get()->get_agent_id() == agent_id; });
		if ((*found_agent).get_agent_id() == agent_id)
			(*found_agent).remove_neighbour(neighbour_id);
	}
};