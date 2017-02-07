PROGS := ftserver ftclient

all: $(PROGS)

chatserve: chatserve.cpp
	g++ -g ftserver.cpp -o ftserver

chatclient: chatclient.c
	gcc -o ftclient ftclient.c
	
clean:
	rm -f $(PROGS) *.o *~
