#Link to Repository: [Lab 4](https://github.com/AshwinK97/Operating-Systems/tree/master/Labs/Lab%204)

## Group 3

## Group members:

Jasindan Rasalingam: 100584595  
Darron Singh: 100584624  
Kaushal Patel: 100586212  
Ashwin Kamalakannan: 100584423



---

### 1.

a. 

We used the First-Fit algorithm as it was the simplest to implement. It also made good use of the FIFO data structure, and was very linear. First-Fit means we allocate the first possible block to the process requesting memory.

b.

We made a queue that holds a process as the head and tail, and then the process would point to the next process. This allows us to save time on the pop and push functions, as we have the head and tail available. 

For memory, we made a memory block structure. Each process struct held a memory struct that accounted for offset, and size. The memory was allocated based on process size and memory availability. If memory had to be allocated and there was enough, we would split it into two chunks, one for the process the other as unallocated. To free the memory we would chnange the allocated flag to 0, and allow it to merge with any adjacent unallocated memory blocks.

c.

d.

An improvement we thought could be made, was shifting the memory blocks to have all unallocated memory either sit at the end, or the beginning. This leads to two benefits.

	1. Space optimization
	2. Easier memory traversal

By splitting the memory into allocated, and unallocated, we have more room to store processes instead of gaps. Some times there may be enough memory for a process, but there won't be a block big enough.

Splitting also also makes it easier to allocate the memory needed for a process. There will be a set offset for the new process to take, instead of traversing and finding a spot. 