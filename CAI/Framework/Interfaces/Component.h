#pragma once
#include "Interface_Mediator.h"

template <class T>
class Component{
protected:
    Interface_Mediator* mediator_;

public:
    Component(Interface_Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Interface_Mediator* mediator) 
    {
        this->mediator_ = mediator;
    }

    virtual void provide_message(T &msg) = 0;

    virtual std::string service_name() = 0;
};