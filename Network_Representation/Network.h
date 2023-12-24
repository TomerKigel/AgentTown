/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/
#pragma once
#include <unordered_map>
#include "Interface_Network_Observer.h"
#include <vector>

template <class T>
class Network
{
public:
	virtual void add_node(int id, int connection) = 0;
	virtual void remove_node(int id) = 0;

	int size() { return nodes.size(); }
	void clear() { nodes.clear(); }
	bool empty() { return nodes.empty(); }

	//Observer Sub
	void subscribe_to_network(Interface_Network_Observer* observer)
	{
		if (observer != nullptr)
			network_observers.push_back(observer);
	}

	void unsubscribe_from_network(const Interface_Network_Observer* observer)
	{
		std::remove_if(network_observers.begin(), network_observers.end(), [observer](const Interface_Network_Observer* a) {return a == observer; });
	}
protected:
	std::unordered_map<int, T> nodes;
	std::vector<Interface_Network_Observer*> network_observers;
};