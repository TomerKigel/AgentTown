#pragma once

#include "message.h"
#include "boost/lexical_cast.hpp"
#include <optional>

namespace message
{
	struct ParsedMessage
	{
	public:
		std::string type;
		std::optional<int> to;
		std::optional<int> from;
		std::optional<double> x_position;
		std::optional<double> y_position;
	};


	inline ParsedMessage parse_message(message& msg)
	{
		ParsedMessage pmsg;
		pmsg.type = msg.header.type;

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