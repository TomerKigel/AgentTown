#pragma once
#include "Interface_Mediator.h"

class Component{
public:
    Component(Interface_Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Interface_Mediator* mediator)
    {
        this->mediator_ = mediator;
    }

    virtual std::string component_name() = 0;
protected:
    Interface_Mediator* mediator_;
};