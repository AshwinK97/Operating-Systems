# Tutorial 7 ~ OS

## Conceptual Questions

1. What are signals? What is their purpose?

    Signals are values used to determine the state and activation instance of events. The purpose of signals is to notify the program if an event has taken place/triggered.

2. Explain **SIGINT, SIGSTOP, SIGCONT**

    **SIGINT**: A signal(program **int**errupt) that is sent when the user types the INTR character (ctrl + c) 

    **SIGSTOP**: A signal used to **stop**/pause a process in its current state.
    
    **SIGCONT**: A signal used to **cont**inue/resume a process that was previously stopped by SIGSTOP.
3. Explain *kill(), waitpid()*

    *kill()*: Used to send a signal to a process or a group of processes. It takes the *pid* to specify what process to send the signal. The signal is also taken from a list given in **<signal.h>** or *0*. 
    
4. Explain a **linked-list** (queue) & what does **FIFO** mean? Common operations?

    A **linked-list** is a list of items linked with the previous item. This is a common data structure. This can be used as a *queue* or a **FIFO** structure by attaching new items to the tail of the list. 

    **FIFO** means *First-In First-Out*, the basic defintion for a queue. The first item to enter a list is the first item accessed.

5. Explain the structure of a linked-list as implemented in C? How would you add/remove values from the queue?

    In C, a linked-list is implemented as nodes. Each node contains a data field and a reference fieid. A head pointer is always used to track the first node, and the last node has a NULL for in it's reference field. Each reference field points to the next node in the list.

    A struct can be used to implement the node structure. To *add* a value, you would make a new node with the value and a NULL reference, and point the current tail reference to the reference of the new node. To *remove* a value, you would point the previous node to the node after and destroy the current node.

## Application Questions