#include "wrapper.h"
#include <errno.h>
#include "common.h"
#include <pthread.h>

#define MAX_SIZE 1024

//generates a message queue identifier, saving it to id, and connects to that message queue, creating it if it does not already exists.
int MQcreate (int *id, char * name)
{
    key_t mq = (key_t)ftok(name, 'm');
    *id = msgget(mq, 0666 | IPC_CREAT);
    if (*id == -1) return 0;
    return 1;
}

//calls MQcreate
int MQconnect (int *id, char * name)
{
    return MQcreate(id, name);
}

//checks if there exist a message of type type in the message queue defined by id
int peek_message( int id, long type )
{
    int result;
    if((result = msgrcv( id, NULL, 0, type,  IPC_NOWAIT)) == -1)
    {
        if(errno == E2BIG)
            return(1);
    }
    return(0);
}

//calls peek_message with type, if it returns 1(true), reads the message from the message queue defined by id and save it to dataBuffer
int MQread (int id, long type, struct messageBuffer *dataBuffer)
{
    int     result, length;
    if(peek_message(id, type)){
    length = sizeof(struct messageBuffer) - sizeof(long);
    if((result = msgrcv(id, dataBuffer, length, type, 0)) == -1)
    {
        return(0);
    }
    return(1);
    }
    return(0);
}

//writes the data from dataBuffer as message to the message queue defined by id
int MQwrite (int id, struct messageBuffer *dataBuffer)
{
    int     result, length;


    length = sizeof(struct messageBuffer) - sizeof(long);
    if((result = msgsnd(id, dataBuffer, length, 0)) == -1)
    {
        return(0);
    }
    return(1);
}

//destroys the message queue defined by id
int MQclose(int id)
{
    if( msgctl(id, IPC_RMID, 0) == -1)
    {
        return(-1);
    }
    return(0);
}

//creats at thread using pthreads, starting functionCall in that thread
int threadCreate (void * functionCall, void* ptr)
{
	pthread_t thread;
    return pthread_create(&thread, NULL, functionCall, ptr);
}



