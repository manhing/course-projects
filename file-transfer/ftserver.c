/*************************************************************************************************
 * ftserver.c
 *
 * Author: Manhing Lei
 * Class: CS 372-400 Fall 2015
 *
 *
 * This program is a server program where a client can request a list of files
 * in the server's current directory or a file to be transferred from there.
 *
 * ***********************************************************************************************
 * Most of the code and the comments related to connecting, sending, receiving
 * came from Beej's Guide found here:
 * http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
 * Also, I am reusing a lot of code from Project 1.
 * ***********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>



#define BACKLOG 10     // how many pending connections queue will hold

#define MAXDATASIZE 500 // max number of bytes we can get at once

/*********************************
*This function will handle signals.
**********************************/
void sigchld_handler(int s)
{
	int status;
	struct sigaction event;

	event.sa_handler = SIG_DFL;
	status = sigaction(SIGINT, &event, 0);
	if (status == -1)
	{
		perror("sigaction");
		exit(1);
	}

}


/*******************************************
 * handleListRequest
 * If client requests a list directory,
 * this function will read in the file names
 * and store them in a string to be sent.
 *******************************************/
void handleListRequest(dataSocket)
{
	DIR *dpdf;
	struct dirent *epdf;
	char fileList[500];
	fileList[0] = '\0';
	//http://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c
	dpdf = opendir("./");
	if (dpdf != NULL)
	{
	   while (epdf = readdir(dpdf))
	   {
		   strcat(fileList, epdf->d_name);
		   strcat(fileList, " ");
		   strcat(fileList, " ");
	   }
	}

	fileList[strlen(fileList)-2] = '\0';

	int len;

	len = strlen(fileList);
	if (sendall(dataSocket, fileList, len) == -1)
	{
	    perror("sendall");
	    printf("We only sent %d bytes because of the error!\n", len);
	}

	printf("List directory sent.\n");

	return;
}

/*****************************************************
 * handleGetRequest
 * This function was intended to read the contexts of
 * a .txt file and sent it to the client.
 *****************************************************/
void handleGetRequest(dataSocket)//(int dataSocket, char *filename)
{
	//http://stackoverflow.com/questions/174531/easiest-way-to-get-files-contents-in-c
	char * buffer = 0;
	long length;
	FILE * f = fopen ("file1.txt", "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = malloc (length);
		if (buffer)
		{
			fread (buffer, 1, length, f);
		}
		fclose(f);
	}

	//printf ("%s\n", buffer);

	return;
}

/*******************************************
 * sendall
 * This function gets call when the list directory
 * or file contexts are ready to be sent to the
 * client.
 *******************************************/
int sendall(int s, char *buf, int len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = len; // how many we have left to send
    int n;
    char str[4];

    str[0] = '\0';
    sprintf(str, "%d", len); //http://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c

    send(s, str, strlen(str), 0);

    while(total < len)
    {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}



int main(int argc, char *argv[])
{
    int sockfd, contfd, datafd;  // listen on sock_fd,
    							//control connection on contfd,
    							//data connection on datafd
    struct sockaddr_in their_addr; // connector's address information
	struct sockaddr_in clientDataAddr;
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char *s;//[INET6_ADDRSTRLEN];
    int rv;
    char buf[MAXDATASIZE];
    int numbytes = 0;
	char filename[30];
	char clientCommand[2];
	char clientDataPort[5];
	int port = atoi(argv[1]);

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(port);
	their_addr.sin_addr.s_addr = INADDR_ANY;

	//start server socket connection
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("server: socket");
		exit(1);
	}

	//bind
	if (bind(sockfd, (struct sockaddr*) &their_addr, sizeof(their_addr)) == -1)
	{
		close(sockfd);
		perror("server: bind");
		exit(1);
	}

    //listen
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("server: listen");
		exit(1);
	}

	//handles zombies
	sa.sa_handler = sigchld_handler; // reap all dead processes
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}

	printf("Server open on %s.\n", argv[1]);

	//main accept() loop
	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		contfd = accept(sockfd, (struct sockaddr *)&clientDataAddr, &sin_size);
		if (contfd == -1)
		{
			perror("accept");
			exit(1);
		}

		printf("Control connection from client successful.\n");

		//receiving client COMMAND
		if ((numbytes = recv(contfd, clientCommand, 2, 0)) == -1)
		{
				perror("recv");
				exit(1);
		}
		clientCommand[2] = '\0';


		int numbytes2 = 0;
		//receiving client Data Port number
		if ((numbytes2 = recv(contfd, clientDataPort, 5, 0)) == -1)
		{
			perror("recv");
			exit(1);
		}
		clientDataPort[numbytes2] = '\0';

		if (numbytes2 == 4)
		{
			printf("added one\n");
			clientDataPort[numbytes2-1] = '\0';
		}


		int numbytes3 = 0;
		if (strcmp(clientCommand, "-g") == 0)
		{
			if ((numbytes3 = recv(contfd, filename, 29, 0)) == -1)
			{
				perror("recv");
				exit(1);
			}
			filename[numbytes3] = '\0';
		}


		/******************************************************
		 * Data Connection starts here
		 ******************************************************/

		int cdp = atoi(clientDataPort);
		clientDataAddr.sin_port = htons(cdp);

		datafd = socket(AF_INET, SOCK_STREAM, 0);
		if (datafd == -1)
		{
			perror("client: socket");
			exit(1);
		}


		int status;
		int countTries = 0;

		//connect
		do
		{
			status = connect(datafd, (struct sockaddr *) &clientDataAddr, sizeof(clientDataAddr));
		} while (status == -1 && countTries < 10);


		if (status == -1)
		{
			perror("client: connect");
			exit(1);
		}

		printf("Data connection with client successful.\n");

		//if command was -l or -g, send requested data
		if (strcmp(clientCommand, "-l") == 0)
		{
			printf("List directory requested...\n");
			handleListRequest(datafd);
		}

		if (strcmp(clientCommand, "-g") == 0)
		{
			//handleGetRequest(datafd, filename);
			handleGetRequest(datafd);
		}

		// Close data connection
		status = close(datafd);
		if (status == -1)
		{
			perror("close");
			exit(1);
		}
		printf("Data connection closed.\n");

	} //end while loop

    return 0;
}
