#pragma once
#include <iostream>
#include <vector>

using std::string;

class Connection
{
public:
	virtual int get_id() const = 0;

	virtual void run() = 0;

	virtual void read() = 0;

	virtual void send(const string& message) = 0;

	virtual void send_to_id_list(const std::string& message, const std::vector<int> id_list) = 0;

	virtual void send_all(const string& message) = 0;

	virtual void disconnect() = 0;
};