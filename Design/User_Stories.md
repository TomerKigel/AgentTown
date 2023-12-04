<h1>User stories</h1>

<h4>Front</h4>
as an ADMIN
<br>I want to create(set up) a new network that will host agents and communications between them</br>
so I can run DCOP experiments
<h4>Back (acceptance criteria)</h4>
-when the framework is requested to create a new network with a network name parameter it should check if an existing network with a given name already exists<br>
 if the network already exists it should abort the attempt to make a new network<br>
 otherwise, it should create a new network and return it to the requester.<br>
-when the framework is requested to create a new network without a network name parameter it should default to 'DEFAULT' network name thus behaving like a singelton<br>
 if there was a previous request for a network without a name, the action should be aborted. otherwise, the network should be created.<br>
<br>
status: incomplete - no support for multiple networks, no framework API support

---
<h4>Front</h4>
as an ADMIN<br>
I want to be able to recreate experiments<br>
so I can compare experiments and revisit previous work I do<br>
<h4>Back (acceptance criteria)</h4>
-when the framework is requested to record, check mode of operation.<br>
  if moo is PAUSED: it should log to a database all messages passing through it once the mode of operation changes to RUNNING<br>
  otherwise, report an error<br>
-when the framework is requested to reconstruct an experiment check mode of operation of the framework<br>
  if moo is PAUSED: drop everything currently being done and start reconstruction -> retrieve setup and messages from the database in chronological order and apply their side effects(i.e. run all records through all active internal systems including the framework)<br>
status: Incomplete - no database, no framework API support<br>
---
