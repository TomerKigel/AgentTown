#pragma once
#include "Interface_Mediator.h"

static enum class system_state { RUNNING, PAUSED, TERMINATED };

template <class T>
class Component{
protected:
    Interface_Mediator* mediator_;
    system_state system_state_;
public:
    
    Component(Interface_Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Interface_Mediator* mediator) 
    {
        this->mediator_ = mediator;
    }

    system_state state()
    {
        return system_state_;
    }

    virtual void provide_message(T &msg) = 0;

    virtual std::string service_name() = 0;
};