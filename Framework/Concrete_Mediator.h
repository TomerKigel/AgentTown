#pragma once
#include "Graphics_Engine/Graphics_Engine.h"
#include "MainServer.h"
#include "Interpreter.h" 
#include "message.h"
#include "Message_Parser.h"
#include "Agent_Network.h"

class Concrete_Mediator : public Interface_Mediator {
public:
    Concrete_Mediator() {}

    Concrete_Mediator(std::initializer_list<Component<message::Message>*> init_message_components, std::initializer_list<Component<message::Parsed_Message>*> init_parsed_message_components) {
        for (auto component : init_message_components)
        {
            add_component(component);
        }
        for (auto component : init_parsed_message_components)
        {
            add_component(component);
        }
    }

    Concrete_Mediator& operator=(Concrete_Mediator&& cm) noexcept
    {
        parsed_message_components_.clear();
        parsed_message_components_.insert(parsed_message_components_.end(), cm.parsed_message_components_.begin(), cm.parsed_message_components_.end());
        message_components_.clear();
        message_components_.insert(message_components_.end(), cm.message_components_.begin(), cm.message_components_.end());
        return *this;
    }

    void push_parsed_message(message::Parsed_Message pmsg)
    {
        auto dest = pmsg.destinations.front();
        for (auto component : parsed_message_components_)
        {
            if (dest == component->service_name())
                component->provide_message(pmsg);
        }
    }

    void push_message(message::Message msg)
    {
        for (auto component : message_components_)
        {
            if (message::Message::message_direction::In == msg.direction && component->service_name().compare("interpreter") == 0)
                component->provide_message(msg);
            if (message::Message::message_direction::Out == msg.direction && component->service_name().compare("main server") == 0)
                component->provide_message(msg);
        }
    }

    void add_component(Component<message::Message>* component)
    {
        component->set_mediator(this);
        message_components_.push_back(component);
    }

    void add_component(Component<message::Parsed_Message>* component)
    {
        component->set_mediator(this);
        parsed_message_components_.push_back(component);
    }

    void remove_component(std::string component_name)
    {
        std::erase_if(message_components_, [component_name](Component<message::Message>* component) {return component_name.compare(component->service_name()) == 0; });
        std::erase_if(parsed_message_components_, [component_name](Component<message::Parsed_Message>* component) {return component_name.compare(component->service_name()) == 0; });
    }

    void remove_component(Component<message::Message>* component)
    {
        std::erase(message_components_, component);
    }

    void remove_component(Component<message::Parsed_Message>* component)
    {
        std::erase(parsed_message_components_, component);
    }

private:
    std::vector<Component<message::Message>*> message_components_;
    std::vector<Component<message::Parsed_Message>*> parsed_message_components_;

};