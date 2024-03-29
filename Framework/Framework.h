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


/*Dependencies*/
#include "MainServer.h"
#include "message.h"
#include "Graphics_Engine/Graphics_Engine.h"
#include "Queue_Manager.h"
#include "Concrete_Mediator.h"
#include "Interpreter.h"
#include "Networks_Manager.h"
#include "Interface_Framework.h"


namespace cai
{
	class Framework : public Interface_Framework
	{
	public:
		Framework();

		~Framework();

		//copying this class is disallowed
		Framework(const Framework&) = delete;


		//******************//
		//  components api  //
		//******************//

		/// <summary>
		/// adds a system to the framework
		/// </summary>
		/// <param name_="system"> - the system to instantiate in the framework<para /> Choices: systems::Graphics, systems::Interpreter, systems::Communications, systems::Representational_Network</param>
		/// <exception cref= "std::runtime_error"> - Thrown when a system is already part of the framework</exception>
		void add_system(systems system);

		/// <summary>
		/// removes a system to the framework
		/// </summary>
		/// <param name_="system"> - the system to remove from the framework.<para /> Choices: systems::Graphics, systems::Interpreter, systems::Communications, systems::Representational_Network</param>
		/// <exception cref= "std::runtime_error"> - Thrown when a system is not part of the framework, not added or already removed</exception>
		void remove_system(systems system);


		//********************************//
		//  representational network api  //
		//********************************//

		/// <summary>
		/// creates a new representational network  <para />
		/// depends on the existence of a <see cref="Network_Representation"/> Component  <para />
		/// thus if an instance was not yet passed to Framework, the Framework will instantiate it automatically.
		/// </summary>
		/// <param name_="network_name"> - The name_ of the new network to be created.  <para />
		/// defaults to 'DEFAULT' if no value is passed
		/// </param>
		void create_network(std::string network_name = "DEFAULT");


		/// <summary>
		/// deletes an existing representational network  <para />
		/// </summary>
		/// <param name_="network_name"> - The name_ of the network to be deleted.</param>
		/// <exception cref="std::runtime_error">- Thrown when invalid name_ is passed</exception> 
		void delete_network(std::string network_name);


		//**************//
		//  utility api //
		//**************//

		/// <summary>
		/// get all system names that were added to the framework
		/// </summary>
		/// <returns> list of system names </returns>
		std::vector<std::string> get_names_of_components();

		
		//********************//
		//  System state api  //
		//********************//

		/// <summary>
		/// change state of a specific system to - RUN
		/// </summary>
		/// <param name_ = "system"> - the system to run, has to have the system previously added </param>
		/// <exception cref="std::runtime_error">- Thrown when attempting to run a system that doesn't exist in the framework</exception> 
		void run(systems system);


		/// <summary>
		/// change state of a specific system to - PAUSE
		/// </summary>
		/// <param name_ = "system"> - the system to pause, has to have the system previously added </param>
		/// <exception cref="std::runtime_error">- Thrown when attempting to pause a system that doesn't exist in the framework</exception> 
		void pause(systems system);


		/// <summary>
		/// change state of all systems in the framework to - RUN
		/// </summary>
		void run_all();


		/// <summary>
		/// change state of all systems in the framework to - PAUSE
		/// </summary>
		void pause_all();


		/// <summary>
		/// terminates and removes all systems on the framework
		/// </summary>
		void close() noexcept;

	private:
		//logging init
		void init_logging_();

		//network configuration variables for the base_server_ system
		std::string host_;
		int port_;

		//handlers of framework systems

		Concrete_Mediator SystemMediator_;
		Graphics_Engine engine_;
		Interpreter interpreter_;
		Networks_Manager networks_manager_;
		MainServer base_server_;

		
		//Thread handlers

		std::thread engine_thread_, interpreter_thread_, representational_network_thread_;

		//vector of all active systems 

		std::unordered_map<systems, activity> map_of_active_components_;
	};
}

