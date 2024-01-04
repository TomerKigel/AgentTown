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
#include "Interface_Mediator.h"

/// <summary>
/// Represents a base class for components participating in the mediator pattern.
/// </summary>
class Component
{
public:
    /// <summary>
    /// Constructor for the Component class.
    /// </summary>
    /// <param name_="mediator">The mediator to associate with the component.</param>
    Component(Interface_Mediator* mediator = nullptr) : mediator_(mediator) {}

    /// <summary>
    /// Set the mediator for the component.
    /// </summary>
    /// <param name_="mediator">The mediator to set.</param>
    void set_mediator(Interface_Mediator* mediator)
    {
        this->mediator_ = mediator;
    }

    /// <summary>
    /// Get the name_ of the component.
    /// </summary>
    /// <returns>The name_ of the component.</returns>
    virtual std::string component_name() = 0;

protected:
    /// <summary>
    /// The mediator associated with the component.
    /// </summary>
    Interface_Mediator* mediator_;
};