<h1>User stories</h1>

<h4>Front</h4>
as an ADMIN
I want to create(set up) a new network that will host agents and communications between them
so I can run DCOP experiments
<h4>Back (acceptance criteria)</h4>
-when the framework is requested to create a new network with a network name parameter it should check if an existing network with a given name already exists
 if the network already exists it should abort the attempt to make a new network
 otherwise, it should create a new network and return it to the requester.
-when the framework is requested to create a new network without a network name parameter it should default to 'DEFAULT' network name thus behaving like a singelton
 if there was a previous request for a network without a name, the action should be aborted. otherwise, the network should be created.

status: incomplete - no support for multiple networks, no framework API support

---
<h4>Front</h4>
as an ADMIN
I want to be able to recreate experiments
so I can compare experiments and revisit previous work I do
<h4>Back (acceptance criteria)</h4>
-when the framework is requested to record, check mode of operation.
  if moo is PAUSED: it should log to a database all messages passing through it once the mode of operation changes to RUNNING
  otherwise, report an error
-when the framework is requested to reconstruct an experiment check mode of operation of the framework
  if moo is PAUSED: drop everything currently being done and start reconstruction -> retrieve setup and messages from the database in chronological order and apply their side effects(i.e. run all records through all active internal systems including the framework)
status: Incomplete - no database, no framework API support
---
