# Conceptual Questions

## 1. What is an ADT?
An ADT (abstract data type) is a mathematical model for data types where the data is defined by its behavior in the point of view of the user. This means that the implementation is hidden, and instead the ADT is described by its operations, possible values and behavior.

## 2. Explain the difference between a Queue and a Stack.
A queue data structure is first in first out, similar to a line at a store. The first person in line will be the first person to exit the line. A stack is last in first out, similar to a stack of plates. We add to the stack at the top and remove elements at the top.

## 3. Name and briefly explain 3 data structures

### Singly linked list
A data structure that is made up of nodes that are linked together. You only need to keep track of the head node, which is the first in the list. Each node contains some data, and a pointer to the next node in line. The last node contains a `NULL` pointer.

### AVL tree
A data structure that is made up of nodes that contain up to 2 child nodes. The left node must be less than or equal to the parent and the right node must be greater than or equal to the parent. Also, the tree must be self balancing. This means that if the height of the tree exceeds log2(n) where n is the number of nodes, the tree must rotate itself so that the height is optimized.

### Graph
A data structure that is made up of vertices that are connected to each other by edges. The each vertex can have multiple other vertices connecting them, however an edge can only have 2 vertices connected.

## 4. What is a binary tree? What are some common operations?
A binary tree is a tree data structure where each node has 2 children nodes. Some of the common operations are traversing, searching. The three types of traversing are in order, pre order and post order traversals.

## 5. What is a hash table? What are some common operations?
A hash table is a data structure that maps values to an array using a key. In order to generate the key, we use a hash function. The hash function converts the value to an integer that capable of mapping to an array. This means that the search time is essentially constant, or as fast as our hash function is. Some common operations are: search(key), add(key, value), remove(key, value) and hash(value).


# Applications Questions

All code and output can be found [here](https://github.com/AshwinK97/Operating-Systems/tree/master/Tutorials/Tutorial%208).

Link to clone repository: git@github.com:AshwinK97/Operating-Systems.git
