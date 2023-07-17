#pragma once
#include <vector>
#include <optional>
#include <string>
#include <iostream>

namespace message
{
	const std::string open_header = "[";
	const std::string close_header = "]";
	const std::string open_message = "{";
	const std::string close_message = "}";

	struct message_header
	{
		std::string type;
		uint32_t body_size = 0;
		uint32_t connection_id = 0;
	};

	struct Message
	{
	public:
		// Header & Body vector
		message_header header;
		std::vector<char> body;
		enum class message_direction{In,Out};
		message_direction direction = message_direction::In;
	};

	// Override for std::cout compatibility - produces friendly description of message
	inline std::ostream& operator << (std::ostream& os, const Message& msg)
	{
		os << "Type:" << msg.header.type << " Size:" << msg.header.body_size << std::endl;
		os << "Message:" << msg.body.data();
		return os;
	}

	inline Message& operator << (Message& msg, const std::vector<char>& data)
	{
		// Cache current size of vector, as this will be the point we insert the data
		size_t i = msg.body.size();

		// Resize the vector by the size of the data being pushed
		msg.body.resize(msg.body.size() + data.size() + 1);

		// Physically copy the data into the newly allocated vector space
		std::memcpy(msg.body.data() + i, data.data(), data.size());

		// Recalculate the message size
		msg.header.body_size = data.size();

		// Return the target message so it can be "chained"
		return msg;
	}

	inline Message& operator << (Message& msg, const std::string& data)
	{
		// Cache current size of vector, as this will be the point we insert the data
		size_t i = msg.body.size();

		// Resize the vector by the size of the data being pushed
		msg.body.resize(msg.body.size() + data.size() + 1);

		// Physically copy the data into the newly allocated vector space
		std::memcpy(msg.body.data() + i, data.data(), data.size());

		// Recalculate the message size
		msg.header.body_size = data.size();

		// Return the target message so it can be "chained"
		return msg;
	}


	inline Message& operator >> (Message& msg, std::vector<char>& data)
	{
		std::memcpy(&data, msg.body.data(), msg.body.size());

		msg.body.resize(0);

		msg.header.body_size = 0;

		return msg;
	}

	inline Message& operator >> (Message& msg, std::string& data)
	{
		//std::memcpy(&data, msg.body.data(), msg.body.size());
		data = msg.body.data();

		msg.body.resize(0);

		msg.header.body_size = 0;

		return msg;
	}

	inline void reset(Message& msg)
	{
		msg.header.body_size = 0;
		msg.header.type = "";
		msg.body.clear();
		msg.body.shrink_to_fit();
		msg.direction = Message::message_direction::In;
		msg.header.connection_id = 0;
	}

	inline std::string to_string(Message& msg)
	{
		return "[" + msg.header.type + "]" + "{" + msg.body.data() + "}";
	}

	inline std::optional<std::string> get_part_of_message(Message& msg,std::string start, std::string end)
	{
		if(msg.body.size() == 0)
			return std::nullopt;

		std::string raw_data = msg.body.data();

		int strt = raw_data.find(start);
		if (strt != -1) {
			auto new_data = raw_data.substr(strt, std::string::npos);
			int after_start = new_data.find(start) + start.length();
			return new_data.substr(after_start, new_data.substr(after_start, std::string::npos).find(end));
		}
		return std::nullopt;
	}
};