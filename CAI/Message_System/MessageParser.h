#pragma once

#include "message.h"
#include "boost/lexical_cast.hpp"
#include <optional>
#include <queue>

namespace message
{
	struct ParsedMessage
	{
	public:
		std::string type;
		int connection_id;
		std::optional<int> new_id;
		std::optional<int> to;
		std::optional<int> from;
		std::optional<double> x_position;
		std::optional<double> y_position;
		std::queue<std::string> destinations;
	};


	inline ParsedMessage parse_message(message& msg)
	{
		ParsedMessage pmsg;
		pmsg.type = msg.header.type;
		pmsg.connection_id = msg.header.connection_id;

		auto new_id = msg.get_part_of_message("new_id:", "\n");
		if (new_id)
			pmsg.new_id = boost::lexical_cast<int>(new_id.value());

		auto to = msg.get_part_of_message("to:", "\n");
		if(to)
			pmsg.to = boost::lexical_cast<int>(to.value());
		
		auto from = msg.get_part_of_message("from:", "\n");
		if (from)
			pmsg.from = boost::lexical_cast<int>(from.value());

		auto x = msg.get_part_of_message("x:", "\n");
		if (x)
			pmsg.x_position = boost::lexical_cast<double>(x.value());

		auto y = msg.get_part_of_message("y:", "\n");
		if (y)
			pmsg.y_position = boost::lexical_cast<double>(y.value());

		return pmsg;
	}

}