#pragma once
#include <unordered_map>

template <class T>
class Network
{
protected:
	std::unordered_map<int,T> nodes;
public:
	virtual void add_node(int id, int connection) = 0;
	virtual void remove_node(int id) = 0;
	int size() { return nodes.size(); }
	void clear() { nodes.clear(); }
	bool empty() { nodes.empty(); }

};