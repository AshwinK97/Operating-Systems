# Conceptual Questions

## 1. What is fork(), how does it differ from multi-threading?
*fork()* is a function that invokes a system call to duplicate the current process. This function takes no arguments and returns the process ID of the new process. The newly created process will be a child process of the process that duplicated itself. Once duplicated, both the parent and child processes will continue to execute the code below the fork instruction.

## 2. What is IPC? Describe methods of performing IPC?
IPC (inter process communication) is is a mechanism which allows processes to communicate with each other and synchronize their actions. The two methods of using IPC are shared memory and message passing.

### Shared memory
Two processes share a common space or memory location where one process produce and store data and another processes can consume it.

### Message passing
This method of communication does not require any kind of shared memory. Instead, two processes will establish a communication link and start exchanging messages using send() and recieve primitives.

## 3. Explain semaphores, how they work and how they differ from mutex?
Semaphores

# Application Questions
All code and output can be found [here](https://github.com/AshwinK97/Operating-Systems/tree/master/Tutorials/Tutorial%206).

Link to clone repository: git@github.com:AshwinK97/Operating-Systems.git