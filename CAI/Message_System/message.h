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

	class Message
	{
	public:

		// Header & Body vector
		message_header header;
		std::vector<char> body;
		enum message_directions{In,Out};
		bool direction = In;

		size_t size() const
		{
			return body.size();
		}

		void reset()
		{
			header.body_size = 0;
			header.type = "";
			body.clear();
			body.shrink_to_fit();
		}

		std::string to_string() const
		{
			return "["+header.type+"]" + "{"+body.data()+"}";
		}

		// Override for std::cout compatibility - produces friendly description of message
		friend std::ostream& operator << (std::ostream& os, const Message& msg)
		{
			os << "Type:" << msg.header.type << " Size:" << msg.header.body_size << std::endl;
			os << "Message:" << msg.body.data();
			return os;
		}

		friend Message& operator << (Message& msg, const std::vector<char>& data)
		{
			// Cache current size of vector, as this will be the point we insert the data
			size_t i = msg.body.size();

			// Resize the vector by the size of the data being pushed
			msg.body.resize(msg.body.size() + data.size()+1);

			// Physically copy the data into the newly allocated vector space
			std::memcpy(msg.body.data() + i, data.data(), data.size());

			// Recalculate the message size
			msg.header.body_size = data.size();

			// Return the target message so it can be "chained"
			return msg;
		}


		friend Message& operator >> (Message& msg, std::vector<char>& data)
		{
			std::memcpy(&data, msg.body.data(), msg.body.size());

			msg.body.resize(0);

			msg.header.body_size = 0;

			return msg;
		}

		std::optional<std::string> get_part_of_message(std::string start, std::string end)
		{
			std::string raw_data = body.data();

			int strt = raw_data.find(start);
			if (strt != -1) {
				auto new_data = raw_data.substr(strt,std::string::npos);
				return new_data.substr(new_data.find(start) + start.length(), new_data.find(end) - (new_data.find(start) + start.length()));
			}
			return std::nullopt;
		}
	};



};