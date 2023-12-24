Framework primary functions:  
	1.) Network initialization  
		The framework should be able to initiate a network of agents. (done)  
		It should be able to connect agents to one another.	(done)  
		It should be able to dictate and share environment parameters such as sync/async and more.  
	2.) Appending new agents to network  
		When an existing network is present the framework should be able to add a new agent  
		to the network and update all existing agents about the newly introduced agent.	 (done)  
		The same goes for agent removal. (done)  
	3.) Historical data collection, graphing, and analysis  
		The framework should be able to collect messages passed between agents given the agents are interested in sharing with the framework.  
		The framework should be able to later analyze the messages and deduce certain things about the traffic within the network.  
		The framework should be able to collect experiment data and scenario data and later graph it on demand and export it.  
	4.) Display and means to debug distributed networks  
		The framework should be able to visually display the network and agents in it. (GUI) (partially done)  
		The framework should offer means of data extraction for debugging.  
    
Secondary functionality:  
	1.) Standardizing communications  
		The framework should rely on a protocol that will make it easy to set up and use the framework.  
	2.) Network security  
		The framework should validate agents and messages passed to ensure the network is isolated.  
	  
    

To Do:  
1.) Network initialization:  
	An internal representation of a network should be established. (done)  
		Required:  
		-network class containing agents (note agent class is abstract, should reconsider whether it should stay abstract or a derived class should take the responsibility of being a network node) | graph data structure  
		-agent class should have a network node interface and must have some ability to communicate with the real agent the instance represents via a socket connection using a connection-id or another identifier.  
		-A Design to communicate with the GUI. A derived class from an agent must implement an Object class interface.    
2.) Appending new agents to network  
	Adding and removing agents should be supported, when the above issues are fixed/implemented, it should be easy to add the functionality to add and remove agents to the network.  
		Required:  
		-add_agent function  
		-remove_agent function  
		-change_agent function (optional, should be done much later)  
3.) Historical data collection, graphing, and analysis  
	An SQL connection should be implemented a database should be constructed.  
		Required tables:  
		-agent_table  
		-agent_neighbour_table  
		-scenario_table  
		...  
	Extra thought is needed to establish and build an operational SQL database.  
4.) Display and means to debug distributed networks  
	The Graphics engine as well as everything inside the GrapphicsEngine folder is reused from a previous project. The files should be reviewed and updated to fit the needs of the framework.  
	Sound and animation are not a priority. Could be left alone or removed. Objects should be reviewed, their main purpose is to display agents.  
	The quadtree implemented in the engine is unrequired currently but might be needed later so it should be left alone along with the AABB class that it relies on.  
	The display options should be expanded.  
	SFML allows adding text easily. This feature should be used to display relevant data about agents. The first feature that should be implemented is displaying text when hovering the mouse of the agent.  
		Required:  
		-Initially hovering the mouse over the agent will display its ID.  
5.) Standardizing communications  
	A protocol should be developed and enforced. Messaging must rely on the protocol to allow easy reading. JSON or other options should be considered as viable options for communication.  
	The most fundamental messages should be in mind:  
	-echo  
	-request to join the network  
	-request to leave the network  
	-sent data message to the neighbor  
	-request environment data  
	-self-assignment data to the server  
