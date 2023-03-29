#pragma once
#include <string>
#include "message.h"

class MessageGenerator
{
public:
	static message::message generate_error_message(std::string type)
	{
		if (type == "new no id")
		{

		}
		else if(type == "")
		{

		}
		message::message a;
		return a;
	}

}; 