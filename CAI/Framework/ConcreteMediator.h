#pragma once
#include "../Framework/ConcreteMediator.h"
#include "../Graphics_Engine/GameEngine.h"
#include "../Server_Communications/MainServer.h"
#include "../Message_Interpreting_System/Interpreter.h" 
#include "../Message_System/message.h"

class ConcreteMediator : public Mediator {
private:
    GameEngine* Graphics;
    Interpreter* SystemInterpreter;
    MainServer* Server;

  

public:
    ConcreteMediator(GameEngine* c1, MainServer* c2, Interpreter* c3) : Graphics(c1), Server(c2), SystemInterpreter(c3) {
        this->Graphics->set_mediator(this);
        this->Server->set_mediator(this);
        this->SystemInterpreter->set_mediator(this);
    } 
   
    ConcreteMediator& operator=(ConcreteMediator && cm)
    {
        this->Graphics = cm.Graphics;
        this->Server = cm.Server;
        this->SystemInterpreter = cm.SystemInterpreter;
        return *this;
    }

    void push_message_in(message::message msg)
    {
        SystemInterpreter->provide_message(msg);
    }

    void push_parsed_message(message::ParsedMessage pmsg)
    {
        auto where = pmsg.destinations.front();
        if(where == "engine")
            Graphics->provide_message(pmsg);
        if (where == "data base")
            //DataBase->provide_message(pmsg);
            ;
    }

    void push_message_out( message::message msg)
    {
        this->Server->provide_message(msg);
    }
};