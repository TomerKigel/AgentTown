#pragma once

namespace message {
    struct Message;
    struct Parsed_Message;
}

class Interface_Mediator
{
public:
    virtual void push_parsed_message(message::Parsed_Message pmsg) = 0;

    virtual void push_message(message::Message msg) = 0;
};