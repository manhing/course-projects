#!/usr/bin/python

# Manhing Lei
# CS 372-400
# Fall 2015
#
# Most of my code came from these three sources:
#   http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
#   https://docs.python.org/2/library/socket.html
#   https://docs.python.org/2/library/struct.html

import socket
import sys
import struct

BACKLOG = 10 #how many pending connections queue will hold



HOST = socket.gethostbyname(sys.argv[1])    # The remote host http://www.tutorialspoint.com/python/python_networking.htm
PORT = int(sys.argv[2])             # The same port as used by the server http://www.tutorialspoint.com/python/python_command_line_arguments.htm
COMMAND = sys.argv[3]
DATAPORT_STR = sys.argv[4]


def main():
    #Only five or six arguments are allowed from command line.
    if (len(sys.argv) < 5):
        print "Too few arguments."
        print "Usage: python ftclient.py <SERVER_HOST> <SERVER_PORT> -l|-g [<FILENAME>] <DATA_PORT>"
        sys.exit(1)

    if (len(sys.argv) > 6):
        print "Too many arguments."
        print "Usage: python ftclient.py <SERVER_HOST> <SERVER_PORT> -l|-g [<FILENAME>] <DATA_PORT>"
        sys.exit(1)


    #Tests user input of server port is an integer. If not, exit.
    #http://stackoverflow.com/questions/12466061/how-can-i-check-if-a-string-has-a-numeric-value-in-it-in-python
    try:
        PORT = int(sys.argv[2])
    except Exception:
        print "Server port is not a number."
        sys.exit(1)

    filename = ""
    #If there were 6 arguments, store requested filename in variable.
    if len(sys.argv) == 6:
        filename = sys.argv[4]
    else:
        filename = None


    #Tests user input of server port is an integer. If not, exit.
    #http://stackoverflow.com/questions/12466061/how-can-i-check-if-a-string-has-a-numeric-value-in-it-in-python
    try:
        if len(sys.argv) == 6:
            DATAPORT_INT = int(sys.argv[5]) #cast as integer
        else:
            DATAPORT_INT = int(sys.argv[4])
    except Exception:
        print "Data port is not a number."
        sys.exit(1)


    #If there was no filename with a get(-g) command, exit.
    if (COMMAND == "-g") and (filename is None):
        print "No file specified."
        print "Usage: python ftclient.py <SERVER_HOST> <SERVER_PORT> -l|-g [<FILENAME>] <DATA_PORT>"
        sys.exit(1)


    # The given command must be either -l (list) or -g (get).
    if (COMMAND != "-l") and (COMMAND != "-g"):
        print "Command must be -l or -g. Please try again."
        sys.exit(1)


    #Server and data ports must be different.
    if PORT == DATAPORT_INT:
        print "Server port and data port must be different."
        sys.exit(1)

    initiateContact(DATAPORT_INT)


#********************************************************
#This function creates a control connection with the server.
#Once successful, it opens a data connection.
#********************************************************
def initiateContact(DATAPORT_INT):
    s = None

    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    except socket.error as msg:
        s = None

    try:
        s.connect((HOST, PORT))
    except socket.error as msg:
        s.close()
        s = None

    if s is None:
        print 'could not open socket'
        sys.exit(1)


    makeRequest(s)


    #Create client-side socket.
    try:
        clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    except Exception:
        print "Error: data connection socket"
        sys.exit(1)

    #Use inputted data port.
    try:
        clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        clientSocket.bind(("", DATAPORT_INT))
    except Exception:
        print "Error: data connection bind"
        sys.exit(1)

    #Listen for connections.
    try:
        clientSocket.listen(BACKLOG)
    except Exception:
        print "Error: data connection listen"
        sys.exit(1)

    #Accept data connection.
    try:
        dataSocket = clientSocket.accept()[0]
    except Exception:
        print "Error: data connection accept"
        sys.exit(1)

    receiveFile(dataSocket)

    s.close()


#**********************************************************
#This function sends the request information to the server.
#
#**********************************************************
def makeRequest(s):
    s.send(COMMAND)

    s.send(DATAPORT_STR)

    if(COMMAND == "-g"):
        s.send(filename)


#*********************************************************************
#This function receives the data sent by the server.
#If a list was requested, it will print out the list.
#If a file was requested, it will write a file to the current directory.
#***********************************************************************
def receiveFile(dataSocket):
    dataLength=""

    length = 2

    while len(dataLength) < length:
        try:
            dataLength += dataSocket.recv(length - len(dataLength))
        except Exception:
            print "Error receiving transfer."
            sys.exit(1);


    dataString = ""
    length = int(dataLength)

    if (COMMAND == "-l"):
        while len(dataString) < length:
            try:
                dataString += dataSocket.recv(length - len(dataString))
            except Exception:
                print "Error receiving list transfer."
                sys.exit(1);


    if (COMMAND == "-g"):
        while len(dataString) < length:
            try:
                dataString += dataSocket.recv(length - len(dataString))
            except Exception:
                print "Error receiving transfer of file."
                sys.exit(1);
        #write file
        with open(filename, "w") as outfile:
            outfile.write(dataString)


    print "\nReceiving directory structure from " +  sys.argv[1] + ":" + DATAPORT_STR
    print dataString + "\n"


#http://stackoverflow.com/questions/4970375/how-to-start-a-program-automatically-from-the-main-method
if __name__ == "__main__":
    main()