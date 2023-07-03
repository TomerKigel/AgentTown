#pragma once
#include <unordered_map>
#include "../AI_Elements/Interfaces/NetworkObserver.h"

template <class T>
class Network
{
protected:
	std::unordered_map<int,T> nodes;
	std::vector<NetworkObserver*> network_observers;
public:
	virtual void add_node(int id, int connection) = 0;
	virtual void remove_node(int id) = 0;

	int size() { return nodes.size(); }
	void clear() { nodes.clear(); }
	bool empty() { nodes.empty(); }

	void subscribe_to_network(NetworkObserver* observer)
	{
		if(observer != nullptr)
			network_observers.push_back(observer);
	}

	void unsubscribe_from_network(const NetworkObserver* observer)
	{
		std::remove_if(network_observers.begin(), network_observers.end(), [observer](const NetworkObserver* a) {return a == observer; });
	}

};