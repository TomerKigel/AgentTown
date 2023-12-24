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