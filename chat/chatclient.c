/*************************************************************************************************
 * chatclient.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Man Hing
 *
 * This program is a server program where a client to connect and send messages back and forth.
 *
 * ***********************************************************************************************
 * Most of the code and the comments related to connecting, sending and receiving
 * came from Beej's Guide found here:
 * http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#simpleserver
 * ***********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>



#define MAXDATASIZE 500 // max number of bytes we can get at once

//gets internet address
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    char handle[10];
    char message[510];



    //if too few arguments in command line, print usage guide
    if (argc < 3)
    {
        fprintf(stderr,"usage: hostname port\n");
        exit(1);
    }

    //Prompt for user's screen name; max 10 characters
    printf("Please enter your screen name: ");
    scanf("%[^\n]%*c", handle);


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //call getaddrinfo function to store information
    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        //connect
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    //convert format
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if (send(sockfd, handle, strlen(handle), 0) == -1)
        perror("send");

    while(1)
    {
    	//prompts for client's message
		printf("%s> ", handle);
	    fgets(buf, sizeof buf, stdin);

	    //add null terminator; fegets seemed to store an extra character in the string.
	    buf[strlen(buf) - 1] = '\0';

	    //if user types in "\quit", close connection and exit program
		if (strcmp(buf, "\\quit") == 0)
		{
			close(sockfd);
			exit(0);
		}

		//concatenate client screen name and input into one message
		strcpy(message, handle);
		strcat(message, "> ");
		strcat(message, buf);

		//if user didn't quit, then send message to client
		if (send(sockfd, message, strlen(message), 0) == -1)
			perror("send");

		//receives message from server
	    if ((numbytes = recv(sockfd, message, MAXDATASIZE-1, 0)) == -1)
	    {
	        perror("recv");
	        exit(1);
	    }

	    //add null terminator
	    message[numbytes] = '\0';

	    //print message to screen
	    printf("ServerHandle> %s\n",message);

    }

    //close connection
    close(sockfd);

    return 0;
}
