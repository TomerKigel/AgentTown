#pragma once
#include "../../Message_System/message.h"
#include "../../Message_System/MessageParser.h"

class Mediator
{
public:
    virtual void push_parsed_message(message::ParsedMessage pmsg) = 0;

    virtual void push_message(message::message msg) = 0;
};