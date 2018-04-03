# Conceptual Questions

## 1. Explain what MPI is, what are it's benefits?
MPI (Message Passing Interface), is a standardized message-passing system that allows applications to work with a wide variety of parallel computing architectures. MPI is essentially a communications protocol for programming parallel computers. Bu unifying the various message passing protocols, MPI makes it easier for developers to write applications that are portable to all major architectures. MPI mixes point-to-point and collaborative communications which allow you to create highly complex parallel applications.

## 2. Explain briefly how MPI supports running on separate computers in a cluster.
In order to run on seperate computers, MPI needs an interface to communicate with between machines. this can be done over a LAN on computers that have been configured with an NFS server connecting via SSH. Or you can setup an amazon EC2 where you can run MPI programs over their cloud computing network. In either case, 1 computer acts as the host and the others act as clients.

## 3. Name **four** MPI data types.
MPI_CHAR, MPI_BYTE, MPI_INT, MPI_LONG.

## 4. Explain MPI_Bcast function.
This function broadcasts a message from the root process to all other processes of the communicator.

## 5. Exmplain MPI_Send and MPI_Recv functions.
The MPI_Send and MPI_Recv functions are used to send and receive data between 2 computers in a network. When one computer wants to send a message to another, it bundles up the data into a single buffer. Then, the data is sent through the network, however it won't be received unless the recipient calls MPI_Recv, acknowledging that it wants to recieve data. The data sent will be in an MPI data type struct.

# Application Questions

All code and output can be found [here](https://github.com/AshwinK97/Operating-Systems/tree/master/Tutorials/Tutorial%2010).

Link to clone repository: git@github.com:AshwinK97/Operating-Systems.git
