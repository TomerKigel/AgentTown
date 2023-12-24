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


		if (const auto new_id = message::get_part_of_message(msg, "new_id:", "\n"))
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