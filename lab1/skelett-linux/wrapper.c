#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include "wrapper.h"




int threadCreate (void * functionCall, int threadParam)
{

	/* Creates a thread running threadFunc */
	/* optional parameters (NULL otherwise)and returns its id! */
	//Hint - Should return error codes
}

int initSocket(int * socketHandle)
{
	//Hint - Should return error codes	
}

int socketConnect(int * socketHandle)
{
	//Optional method
	//If you want to use TCP sockets, this method should be implemented
	//In case you want help understanding the differences of sockets
	//Send me mail, come to my office or talk to me during lab:)
	//- Jakob
	//Hint - should return error codes
}

int readFromSocket(int * socketHandle, void * outMsg, int msgSize) 
{
	//int len = 0;
	//ioctl(sock, FIONREAD, &len);
	//use ioctl if you want a dynamic length of the read

	/* Write a msg to a mailslot, return nr */
	/* of successful bytes written         */
	//Hint - Should return error codes
}

int writeToSocket(int * socketHandle, void * intMsg, int msgSize) 
{

	/* Read a msg from a mailslot, return nr */
	/* of successful bytes read              */
	//Hint - Should return error codes
}

int socketClose(int * socketHandle)
{
	
	//Hint - Should return error codes
}


