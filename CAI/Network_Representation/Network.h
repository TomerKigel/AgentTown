#pragma once
#include <vector>

template <class T>
class Network
{
protected:
	std::vector<T&> nodes;
public:
	virtual void add_node(int id, int connection) = 0;
	virtual void remove_node(int id) = 0;
	int size() { return node.size(); }
	void clear() { nodes.clear(); }
	bool empty() { nodes.empty(); }
};