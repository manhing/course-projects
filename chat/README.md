## Chat Client and Server Programs

**INSTRUCTIONS**

1. Unzip and save files in the same directory.

2. To compile, be sure to include the makefile in the same directory and then type "make" in the command line.

3. To execute, first start the server program. Type "./chatserve ####" where #### is any number above 1024. The higher the better.

4. Open another instance of a terminal. I used PuTTY, so I had two PuTTY terminals open.

5. In the second terminal, navigate to the very same directory. Type in "./chatclient localhost ####" where #### is the same number you selected in Step 3.

6. The client program will prompt you for a screen name. Choose one with 10 or less characters.

7. Send messages back and forth between the server and client by alternating turns.

8. To quit either program, use CTRL+C or type in "\quit". The server may not immediately exit since it may be the child process that was exited. Repeat with CTRL+C or "\quit" to continue to exit.