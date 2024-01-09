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
#include <string>
#include <vector>
#include "Component.h"




class Interface_Framework
{
public:
	//components api

	enum class systems { Graphics, Interpreter, Communications, Representational_Network };
	enum class activity { Active, InActive };

	virtual void add_system(systems system) = 0;

	virtual void remove_system(systems system) = 0;

	// representational network api

	virtual void create_network(std::string network_name = "DEFAULT") = 0;

	virtual void delete_network(std::string network_name) = 0;


	// utility api

	virtual std::vector<std::string> get_names_of_components() = 0;


	// system state api

	virtual void run(systems system) = 0;

	virtual void pause(systems system) = 0;

	virtual void run_all() = 0;

	virtual void pause_all() = 0;

	virtual void close() noexcept = 0;
};