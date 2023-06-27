#pragma once
#include "Mediator.h"

template <class T>
class Component{
protected:
    Mediator* mediator_;

public:
    Component(Mediator* mediator = nullptr) : mediator_(mediator) {}

    void set_mediator(Mediator* mediator) 
    {
        this->mediator_ = mediator;
    }

    virtual void provide_message(T &msg) = 0;

    virtual std::string service_name() = 0;
};