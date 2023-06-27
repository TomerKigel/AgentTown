#pragma once
#include "../Framework/ConcreteMediator.h"
#include "../Graphics_Engine/GraphicsEngine.h"
#include "../Server_Communications/MainServer.h"
#include "../Message_Interpreting_System/Interpreter.h" 
#include "../Message_System/message.h"
#include "../Message_System/MessageParser.h"
#include "../Network_Representation/Agent_Network.h"

class ConcreteMediator : public Mediator {
private:
    GraphicsEngine* Graphics;
    Interpreter* SystemInterpreter;
    MainServer* Server;
    Agent_Network* AgentNetwork;

    std::vector<Component<message::message>*> message_components;
    std::vector<Component<message::ParsedMessage>*> parsed_message_components;
    

public:
    ConcreteMediator(std::initializer_list<Component<message::message>*> init_message_components, std::initializer_list<Component<message::ParsedMessage>*> init_parsed_message_components){
        for (auto component : init_message_components)
        {
            component->set_mediator(this);
            message_components.push_back(component);
        }
        for (auto component : init_parsed_message_components)
        {
            component->set_mediator(this);
            parsed_message_components.push_back(component);
        }
    } 
   
    ConcreteMediator& operator=(ConcreteMediator && cm)
    {
        parsed_message_components.clear();
        parsed_message_components.insert(parsed_message_components.end(), cm.parsed_message_components.begin(), cm.parsed_message_components.end());
        message_components.clear();
        message_components.insert(message_components.end(), cm.message_components.begin(), cm.message_components.end());
        return *this;
    }

    void push_parsed_message(message::ParsedMessage pmsg)
    {
        auto dest = pmsg.destinations.front();
        for (auto component : parsed_message_components)
        {
            if (dest == component->service_name())
                component->provide_message(pmsg);
        }
    }

    void push_message(message::message msg)
    {
        for (auto component : message_components)
        {
            if (msg.In == msg.direction && component->service_name().compare("interpreter") == 0)
                component->provide_message(msg);
            if (msg.Out == msg.direction && component->service_name().compare("main server") == 0)
                component->provide_message(msg);
        }
    }
};