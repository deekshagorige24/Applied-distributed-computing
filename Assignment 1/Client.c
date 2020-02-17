//**********************#
//A simple Client server application
//**********************#
// Author : Deeksha Rao Gorige//
// 	    SreeNavya  
//	    Simar		#
// Date   : Jan 28,2020     #
// Group  : 8         #
//**********************#
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define MAX 1024
#define PORT 2525

void chat_session(int sockfd)
{
	char buff[MAX];
	time_t rawtime;
	//iterates infinetely for chat
	while(1) {
	  //clears the buffer and writes to the server
	  memset(buff,0,sizeof(buff));
	  printf("To Server : ");
	  fgets(buff,1024,stdin);
	  write(sockfd, buff, sizeof(buff));
	  //clears the buffer and reads a string from the user to send to the server
	  memset(buff,0, sizeof(buff));
	  read(sockfd, buff, sizeof(buff));
	  //function to get the timestamp
	  time(&rawtime);
	  char *time_readable=strdup(ctime(&rawtime));
	  int string_size = strlen(time_readable);
	  time_readable[string_size -1]= '\0';
	  printf("Message Received on %s From Server : %s", time_readable,buff);
	  free(time_readable);
	  //if the msg contains "Quit" then the client exit and chat gets ended
	  if ((strncmp("Quit", buff, 4)) == 0) {
	    printf("Chat ended...Client exiting...\n");
	    break;
	  }

	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	// creating a scoket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	memset(&servaddr,0, sizeof(servaddr));

	// assign IP address, PORT address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("52.90.92.71");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	chat_session(sockfd);
	// close the socket
	close(sockfd);
}
