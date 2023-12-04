# User Stories

## Front

### As an ADMIN
I want to create (set up) a new network that will host agents and communications between them
so I can run DCOP experiments.

## Back (Acceptance Criteria)
- When the framework is requested to create a new network with a network name parameter, it should check if an existing network with the given name already exists.
  - If the network already exists, it should abort the attempt to make a new network.
  - Otherwise, it should create a new network and return it to the requester.
- When the framework is requested to create a new network without a network name parameter, it should default to 'DEFAULT' network name, thus behaving like a singleton.
  - If there was a previous request for a network without a name, the action should be aborted. Otherwise, the network should be created.

[![Status](https://img.shields.io/badge/Status-Incomplete-red)](https://img.shields.io/badge/Status-Incomplete-red)

---

## Front

### As an ADMIN
I want to be able to recreate experiments
so I can compare experiments and revisit previous work.

## Back (Acceptance Criteria)
- When the framework is requested to record, check the mode of operation.
  - If the mode of operation is PAUSED, it should log to a database all messages passing through it once the mode of operation changes to RUNNING.
  - Otherwise, report an error.
- When the framework is requested to reconstruct an experiment, check the mode of operation of the framework.
  - If the mode of operation is PAUSED, drop everything currently being done and start reconstruction.
  - Retrieve setup and messages from the database in chronological order and apply their side effects (i.e., run all records through all active internal systems, including the framework).

[![Status](https://img.shields.io/badge/Status-Incomplete-red)](https://img.shields.io/badge/Status-Incomplete-red)
