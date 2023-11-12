//#pragma once
//#include <unordered_map>
//#include "Interface_Network_Observer.h"
//
//template <class T>
//class Network
//{
//protected:
//	std::unordered_map<int,T> nodes;
//	std::vector<Interface_Network_Observer*> network_observers;
//public:
//	virtual void add_node(int id, int connection) = 0;
//	virtual void remove_node(int id) = 0;
//
//	int size() { return nodes.size(); }
//	void clear() { nodes.clear(); }
//	bool empty() { nodes.empty(); }
//
//	//Observer Sub
//	void subscribe_to_network(Interface_Network_Observer* observer)
//	{
//		if(observer != nullptr)
//			network_observers.push_back(observer);
//	}
//
//	void unsubscribe_from_network(const Interface_Network_Observer* observer)
//	{
//		std::remove_if(network_observers.begin(), network_observers.end(), [observer](const Interface_Network_Observer* a) {return a == observer; });
//	}
//
//};