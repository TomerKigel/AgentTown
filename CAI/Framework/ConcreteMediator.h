#pragma once
#include "../Framework/ConcreteMediator.h"
#include "../Graphics_Engine/GameEngine.h"
#include "../Server_Communications/MainServer.h"
#include "../Message_Interpreting_System/Interpreter.h" 
#include "../Message_System/message.h"
#include "../Network_Representation/Agent_Network.h"

class ConcreteMediator : public Mediator {
private:
    GameEngine* Graphics;
    Interpreter* SystemInterpreter;
    MainServer* Server;
    Agent_Network* AgentNetwork;
  

public:
    ConcreteMediator(GameEngine* c1, MainServer* c2, Interpreter* c3, Agent_Network* c4) : Graphics(c1), Server(c2), SystemInterpreter(c3) , AgentNetwork(c4){
        this->Graphics->set_mediator(this);
        this->Server->set_mediator(this);
        this->SystemInterpreter->set_mediator(this);
        this->AgentNetwork->set_mediator(this);
    } 
   
    ConcreteMediator& operator=(ConcreteMediator && cm)
    {
        this->Graphics = cm.Graphics;
        this->Server = cm.Server;
        this->SystemInterpreter = cm.SystemInterpreter;
        this->AgentNetwork = cm.AgentNetwork;
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
        if (where == "representational network")
            AgentNetwork->provide_message(pmsg);
        if (where == "data base")
            //DataBase->provide_message(pmsg);
            ;
    }

    void push_message_out( message::message msg)
    {
        this->Server->provide_message(msg);
    }
};