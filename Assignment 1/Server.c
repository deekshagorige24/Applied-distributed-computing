//**********************#
//A simple Client server application
//**********************#
// Author : Deeksha Rao Gorige #
// Date   : Jan 28,2020     #
// Group  : 8         #
//**********************#
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 1024
#define PORT 2525
# include <fcntl.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <time.h>
// Function for chat between client and server.
void chat_session(int sockfd)
{
	char buff[MAX];
	time_t rawtime;
	// iterates infinetely for chat
	while(1) {
	  memset(buff,0, MAX);
	  // read the message from client and copy into thebuffer
	  int bytes = read(sockfd, buff, sizeof(buff));
	  //Function to get the timestamp
	  time ( &rawtime );
	  char *time_readable = strdup(ctime(&rawtime));
	  int string_size = strlen(time_readable);
	  time_readable[string_size - 1] = '\0';
	  printf("Message recieved  on %s from client: %s", time_readable, buff);
	  free(time_readable);
	  printf("To client: ");
	  //Clears the buffer and reads a string from the user to send to client
	  memset(buff,0, MAX);
	  fgets(buff,1024,stdin);
	  write(sockfd, buff, sizeof(buff));

	  // if msg contains "Quit" then server exit and chat gets ended.
	  if (strncmp("Quit", buff, 4) == 0) {
	    printf("Chat Ended......Server Exiting!!! \n");
	    break;
	  }
	}
}

int main()
{
  int sockfd;
  int connfd;
  socklen_t len;
  struct sockaddr_in serveradd, client;

  // creating a socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully created..\n");
  memset(&serveradd,0, sizeof(serveradd));

  // assign IP address, PORT address
  serveradd.sin_family = AF_INET;
  serveradd.sin_addr.s_addr = htonl(INADDR_ANY);
  serveradd.sin_port = htons(PORT);

  // Binding newly created socket to given IP address
  if ((bind(sockfd, (struct sockaddr*)&serveradd, sizeof(serveradd))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  }
  else
    printf("Socket successfully binded..\n");

  // Now server is ready to listen
  if ((listen(sockfd, 8)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  }
  else
    printf("Server listening..\n");
  len = sizeof(client);

  // Accept the data packet from client i.e accepts the request from the client
  connfd = accept(sockfd, (struct sockaddr*)&client, &len);
  if (connfd < 0) {
    printf("server acccept failed...\n");
    exit(0);
	}
  else
    printf("server acccept the client...\n");

  // Function for chating between client and server
  chat_session(connfd);

  // After the chat, connection is closed
  close(sockfd);
}
