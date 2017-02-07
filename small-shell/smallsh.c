/*
 * smallsh.c
 *
 *  Created on: Aug 3, 2015
 *      Author: Manhing Lei
 *      CS 344 Summer 2015
 */

// A lot of credit goes to http://stephen-brennan.com/2015/01/16/write-a-shell-in-c/


#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>

struct sigaction act;


int cdCommand(char **args);
int exitCommand(char **args);
int EXITVAL; //global variable holds exit value

//list of built-ins other than status
char *builtinStr[] = {
  "cd",
  "exit"
};

int (*builtinFunc[]) (char **) = {
  &cdCommand,
  &exitCommand
};

int numBuiltins() {
  return sizeof(builtinStr) / sizeof(char *);
}

/**************************************
 * This function changes the directory
 * within the shell
 * if user entered "cd". (Built-in)
 * ************************************/
int cdCommand(char **args)
{
	if (args[1] == NULL)
	{
		//if cd was the only argument, change to HOME directory
		chdir(getenv("HOME"));
	}
	else
	{
		//else, change to the folder in the second argument
		if (chdir(args[1]) != 0)
		{
			perror("folder");
		}
	}
	return 1;
}


/**************************************
 * This function exits the shell
 * if user entered "exit". (Built-in)
 * ************************************/
int exitCommand(char **args)
{
  return 0;
}


/**************************************************
 * This function forks the processes
 * ***********************************************/
int runExec(char **args)
{
	pid_t pid, wpid, exitpid;
	int status;
	int exitMethod;
	int fd;
	int fd2;

	//if status was the argument, print last exit value
	if (strcmp(args[0], "status")==0)
	{
		printf("exit value %d\n", EXITVAL);
		return 1;
	}

	//fork
	pid = fork();


	//where IO redirection code goes
/*	if(strcmp(args[0], "ls") == 0 && args[1] != NULL)
	{


		fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}

		fd2 = dup2(fd, 1);
		if (fd2 == -1);
		{
			perror("dup2");
			exit(2);
		}
	}
*/

	//Child process
	if (pid == 0)
	{
		//signal handler
		act.sa_handler = SIG_DFL;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);

		//if cannot complete command, print error
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
    //Error forking
    perror("forking");
	}
	else {
    //Parent process
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED); //store process id
			EXITVAL = WEXITSTATUS(status); //store exit value

		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

		//if command was sleep, print process id and exit value
		if (strcmp(args[0], "sleep") == 0)
		{
			printf("background pid %d is done: exit value %d\n", wpid, EXITVAL);
		}
	}

	return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int runCommand(char **args)
{
	//signal handler
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);

	int i;

	//If an empty string was entered
	if (args[0] == NULL)
	{
		return 1;
	}

	//If a # character was entered, ignore as a comment
	if (strcmp(args[0], "#") == 0)
	{
		return 1;
	}

	//This built-in was created because I couldn't get the I/O redirection working
	//If "ls > [filename]" is entered, store file listing to [filename]
	if(strcmp(args[0], "ls") == 0 && args[1] != NULL)
	{
		if (strcmp(args[1], ">") == 0)
		{
			DIR *d;
			struct dirent *dir;
			d = opendir("."); //open current directory

			if (d)
			{
				FILE *f = fopen(args[2], "w+");
	    			if (f == NULL)
	    			{
	    				//if cannot open file
	    				printf("Error opening file!\n");
	    			//	exit(1);
	    			}
	    		while ((dir = readdir(d)) != NULL)
	    		{
	    			//write file name to file if not "." or ".."
	        		if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
	        		{
	        			//Write filename into file
	        			fprintf(f, "%s\n", dir->d_name);
	        		}
	    		}

	    		closedir(d); //close directory
	    		fclose(f); // close file
			}
		}
		return 1;
	}




	//this is semi-built-in that handles "wc" command since I could not get I/O redirection working
	if(strcmp(args[0], "wc") == 0 && args[1] != NULL)
	{
		//this removes "<" from the second element, then moves the third element to the second element.
		//the exec function can handle the two arguments already without the "<", although it additionally prints the filename
		if (strcmp(args[1], "<") == 0)
		{
			args[1] = args[2];
			args[2] = NULL;
		}
	}


	//if there is a 3rd argument
	if (args[2] != NULL)
	{
		//if it is &, make it NULL before passing to exec
		if (strcmp(args[2], "&") == 0)
			  args[2] = NULL;
	}

	//loop that checks for built-ins
	for (i = 0; i < numBuiltins(); i++)
	{
		if (strcmp(args[0], builtinStr[i]) == 0)
		{
			//if matches a built-in command, run the built-in function
			return (*builtinFunc[i])(args);
		}
	}

	//if not a built-in, run it through exec
	return runExec(args);
}


/***************************************
 * This function takes in a string
 * from the user from standard input
 ***************************************/
char *getString(void)
{
	int bufsize = 2048;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;

	//makes sure malloc was successful
	if (!buffer)
	{
		fprintf(stderr, "smallsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	//loop that takes in a string from standard input
	while (1)
	{
		// Read a character on at a time
		c = getchar();

		// If we hit a new line character, replace it with a null character and return.
		if (c == '\n')
		{
			buffer[position] = '\0';
			return buffer;
		}
		else //else store the character in the buffer
		{
			buffer[position] = c;
		}
		//increment index of buffer
		position++;
	}
}


/******************************************************
 * This function takes in the string from user and
 * parses the words using white space characters
 * as the delimiters and returns an array of
 * words
 *****************************************************/
char **parseString(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokenArray = malloc(bufsize * sizeof(char*));
	char *token;

	//checks to see if malloc was successful
	if (!tokenArray)
	{
		fprintf(stderr, "smallsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	//loop that uses strtok to go from word to word
	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		//store each word as an element of an array
		tokenArray[position] = token;

		//increment index of array
		position++;

		//move to next word
		token = strtok(NULL, " \t\r\n\a");
	}
	//assign NULL to the element after the last word
	tokenArray[position] = NULL;
	return tokenArray;
}


/*****************************************************
 * This function loops the prompt and calls functions
 * to run the string commands
 ****************************************************/
void loopPrompt(void)
{
  char *line;
  char **args;
  int status;

  //Loops the prompt and calls functions to run the string commands
  do
  {
    printf(": ");
    line = getString();
    args = parseString(line);
    status = runCommand(args);

    free(line);
    free(args);
  } while (status);
}



int main(int argc, char **argv)
{
  //Run loop.
  loopPrompt();

  return 0;
}
