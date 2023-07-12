#pragma once

#include "message.h"
#include "boost/lexical_cast.hpp"
#include <optional>
#include <queue>

namespace message
{
	struct Parsed_Message
	{
	public:
		std::string type;
		int connection_id = -1;
		std::optional<int> new_id;
		std::optional<int> to;
		std::optional<int> from;
		std::optional<double> x_position;
		std::optional<double> y_position;
		std::queue<std::string> destinations;
	};


	inline Parsed_Message parse_message(Message& msg)
	{
		Parsed_Message pmsg;
		pmsg.type = msg.header.type;
		pmsg.connection_id = msg.header.connection_id;

		if(const auto new_id = message::get_part_of_message(msg,"new_id:", "\n"))
			pmsg.new_id = boost::lexical_cast<int>(new_id.value());

		if (const auto to = message::get_part_of_message(msg, "to:", "\n"))
			pmsg.to = boost::lexical_cast<int>(to.value());
		
		if (const auto from = message::get_part_of_message(msg, "from:", "\n"))
			pmsg.from = boost::lexical_cast<int>(from.value());

		if (const auto x = message::get_part_of_message(msg, "x:", "\n"))
			pmsg.x_position = boost::lexical_cast<double>(x.value());

		if (const auto y = message::get_part_of_message(msg, "y:", "\n"))
			pmsg.y_position = boost::lexical_cast<double>(y.value());

		return pmsg;
	}

}