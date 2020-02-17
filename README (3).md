# A simple Client-server application
This Program will implement a client server application using TCP connection.

### Header files
For this application i.e 'Chat-Server application', the socket programming header files are imported. The main socket programming header files include <sys/socket.h>, <arpa/inet.h>, <sys/types.h>, <netinet/in.h>, <netdb.h> etc.
| <sys/socket.h> | This header file contains all the data definitions and socket structures
| <arpa/inet.h>  | This header makes available the type sin_port and the the type sin_addr as defined in the program
| <sys/types.h>  | This header file contains data type definitions
| <netinet/in.h> | This header file defined the Internet constants and structures
| <netdb.h>      | This header file contains data definitions for socket subroutines

### Attributes

| **Field** | **Description** |
| --------- | --------------- |
| buff | It is for storing messages. It is given MAX(80) capacity
| rawtime | It returns the current time and date when the message was sent or received. It is assigned to time_t type which is datatype in the C library defined for storing system time values
| sockfd  | It is a listening socket descriptor.
| connfd  | It is a file descriptor returned after a connection has been established. We can use this file descriptor to read messages from and send messages to the client.
| len | It returns the length and it is being assigned to an unsigned opaque integral type of length 32-bits
| severadd | It basically deals with the server address and it is of type struct sockaddr_in which is a structure that makes it easy to reference elements of the socket address.
| client   | It basically deals with the client address and it is of type struct sockaddr_in which is a structure that makes it easy to reference elements of the socket address.

#Methods used and Description
Whenever there is a requirement of communication between a client and a sever we need socket programming. This involves the following steps-

### Socket()

This method creates a socket i.e creates an endpoint for any network connection. It contains three parameters-domain, type, protocol. For this project the server domain was AF_INET which simply means the socket can communicate with IPv4 addresses. Type is the type of connection used. This project involves TCP connection. Protocol is set to '0'. This method when returns '-1' it simply means the socket creation is failed.

### bind()

This method binds the newly created socket to the given IP address. It contains three parameters- sockfd, (struct sockaddr*)&serveradd, address length. sockfd is the file descriptor returned by the socket(), serveradd is a pointer to a valid sockaddr structure cast as a sockaddr* pointer, address length is the length of the sockaddr structure. If the method is not equal to zero which simply means the socket binding has failed else it is successful.

### listen()

Once the binding is successful, the server is now ready to listen or wait for the connection from the client. It has two parameters- sockfd and the Max connections. sockfd which is basically returned by the socket() and Maxconn which is the maximum length of the pending connections.

### accept()

Once the connection has been established the server is now ready to accept the request from the client. It has three parameters - sockfd, (struct sockaddr*)&Client and length. sockfd which is in listen state, length which is a pointer to size of the client structure.

### chat_session()

This method runs until the quit message is given by the user. For each iteration it sets the buffer to zero and reads the message from the connection file descriptor with the help of read(). As soon as it reads a message it takes a time stamp to log the time of the recieved message. The time function is used to get the timestamp. The time function returns time in a raw format. Converting it into a human readable format is done using ctime. Strdup is used so that the next line character returned by ctime can be removed. Memory allocated by strdup is freed after the message is logged. Next it clears the buffer and reads a string input from the user to send to the client. This message is sent to the client using the write() method. If the message entered by the user is "Quit" the chat session ends.

### Close()

Once the chat session ends, the connection is closed.
