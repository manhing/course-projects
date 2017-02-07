## File Transfer Client and Server Programs

**INSTRUCTIONS**

1. Save files in the same or different directories.

2. To compile ftserver.c, navigate to the directory, type `gcc -o ftserver ftserver.c` in the command line.

3. Start running the server by typing in `ftserver #####`, where ##### is any port number above 1024.

4. Open another instance of a terminal for the client program. I used PuTTY, so I had two PuTTY terminals open.

5. In the second terminal, navigate to the very same directory. 

6. To retrieve a directory listing from the server, type in the command line:
	`python ftclient <server> <server-port-number> -l <desired-data-port-number>`, 
	where <server> is the server where ftserver is running;
	where <server-port-number> is the same number used in Step 3;
	where <desired-data-port-number> is a different port number than in Step 3 and above 1024.

7. To retrieve a file from the server, type in the command line:
	`python ftclient <server> <server-port-number> -g <file-name> <desired-data-port-number>`.

8. ftclient.py will exit after each request and retrieval. To exit ftserver, type CTRL+C.