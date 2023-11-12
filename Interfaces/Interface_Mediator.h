#pragma once
//#include "../CAI/Message_System/Message_Parser.h"
//#include "../CAI/Message_System/message.h"

namespace message {
    class Message;
    class Parsed_Message;
}

class Interface_Mediator
{
public:
    virtual void push_parsed_message(message::Parsed_Message pmsg) = 0;

    virtual void push_message(message::Message msg) = 0;
};