#pragma once
#include "Graphics_Engine/Graphics_Engine.h"
#include "MainServer.h"
#include "Interpreter.h" 
#include "message.h"
#include "Message_Parser.h"
#include "Agent_Network.h"
#include "System.h"

class Concrete_Mediator : public Interface_Mediator {
public:
    Concrete_Mediator() {}

    Concrete_Mediator(std::initializer_list<Component*> init_components) {
        for (auto component : init_components)
        {
            add_component(component);
        }
    }

    Concrete_Mediator& operator=(Concrete_Mediator&& cm) noexcept
    {
        components_.clear();
        components_.insert(components_.end(), cm.components_.begin(), cm.components_.end());
        return *this;
    }

    void push_parsed_message(message::Parsed_Message pmsg)
    {
       auto dest = pmsg.destinations.front();
        for (auto component : components_)
        {
            Agent_Network* network = dynamic_cast<Agent_Network*>(component);
            if(network)
            {
                network->provide_message(pmsg);
                break;
            }
        }
    }

    void push_message(message::Message msg)
    {
        auto dest = msg.direction;
        for (Component* component : components_)
        {
            Interpreter* interpreter = dynamic_cast<Interpreter*>(component);
            if (interpreter && dest == message::Message::message_direction::In)
            {
                interpreter->provide_message(msg);
                break;
            }
            MainServer* server = dynamic_cast<MainServer*>(component);
            if (server && dest == message::Message::message_direction::Out)
            {
                server->provide_message(msg);
                break;
            }
        }
    }

    void add_component(Component* component)
    {
        component->set_mediator(this);
        components_.push_back(component);
    }

    void remove_component(Component* component)
    {
        std::erase(components_, component);
    }

private:
    std::vector<Component*> components_;

};