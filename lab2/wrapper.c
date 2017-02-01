#include "wrapper.h"
#include <errno.h>

#define MAX_SIZE 1024

int MQcreate (int *id, char * name)
{
    key_t mq = (key_t)ftok(name, 'm');
    *id = msgget(mq, 0666 | IPC_CREAT);
    if (*id == -1) return 0;
    return 1;
}

int MQconnect (int *id, char * name)
{
    return MQcreate(id, name);
}

int peek_message( int id, long type )
{
    int result, length;
    if((result = msgrcv( id, NULL, 0, type,  IPC_NOWAIT)) == -1)
    {
        if(errno == E2BIG)
            return(1);
    }                       
    return(0);
}

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

int MQwrite (int id, struct messageBuffer *dataBuffer)
{   
    int     result, length;

    /* The length is essentially the size of the structure minus sizeof(mtype) */
    length = sizeof(struct messageBuffer) - sizeof(long);        
    if((result = msgsnd(id, dataBuffer, length, 0)) == -1)
    {
        return(0);
    }                                
    return(1);
}

int MQclose(int id)
{
    if( msgctl(id, IPC_RMID, 0) == -1)
    {
        return(-1);
    }        
    return(0);
}

int threadCreate (void * functionCall, int threadParam)
{
	/* Creates a thread running threadFunc */
	/* Should return 1 on success and 0 on fail*/

	pthread_t thread;
    int* par = (void *)calloc(sizeof(int), 1);
    *par = threadParam;
	return pthread_create(&thread, NULL, functionCall, par);
}



