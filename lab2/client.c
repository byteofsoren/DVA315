#include <stdio.h>
#include <string.h>
#include "wrapper.h"

#define PLANETS 1000000
#define PLANETIPC "PlanetLab"
mqd_t serverHandle;
int connectToServer(char * name)
{
	int errorCode = 0;
	//Create a socket to handle communication with client
	errorCode = MQconnect (&serverHandle, name);
	return errorCode;
}


int main()
{
	//Instead of using a returnhandle, we instead use a global mailslot handle (serverHandle)
	//I think this is more convenient, however, would you could alter the method so that it
	//returns a handle
	int ec = 0; 
	if ((ec = connectToServer(PLANETIPC))==0)
	{
		printf("Failed to connect to server!");
	}
	while(1)
	{

		//Obviously, since you have already made mailslot read compatible with the
		//Planet struct, you should send a planet to the server

		//Instructions as following:
		//Initialize a planet struct
		//Send the planet struct to the server using MQwrite(&serverHandle)
		//if write is success, then you are very well on your way to a planet system 
	}
	if ((ec = MQclose(&serverHandle, PLANETIPC))==0)
	{
		printf("Failed to close server, watch out for memory leaks");
	}
	return 0;
}
