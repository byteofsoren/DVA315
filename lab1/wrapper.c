#include "wrapper.h"
#include <errno.h>

#define MAX_SIZE 1024

int MQcreate (int *id, char * name)
{
<<<<<<< HEAD
    key_t mq = (key_t)ftok(name, 'm');
    *id = msgget(mq, 0666 | IPC_CREAT);
    if (*id == -1) return 0;
    return 1;
=======
    /* Creates a mailslot with the specified name. Uses mq as reference
     * pointer, so that you can reach the handle from anywhere
     * Should be able to handle a messages of any size
     * Should return 1 on success and 0 on fail*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_CREAT | O_RDWR, &attr);
    return (mqd_t)-1 != *mq;
>>>>>>> 2b3273095f24148776cef1b86a714072220eb829
}

int MQconnect (int *id, char * name)
{
<<<<<<< HEAD
    return MQcreate(id, name);
=======
    /* Connects to an existing mailslot for writing Uses mq as reference pointer,
     * so that you can 	reach the handle from anywhere
     * Should return 1 on success and 0 on fail*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_RDWR, &attr);
    //perror("mq_open");
    return (mqd_t)-1 != *mq;
>>>>>>> 2b3273095f24148776cef1b86a714072220eb829
}

int MQread (int id, long type, struct messageBuffer *dataBuffer)
{
<<<<<<< HEAD
    int     result, length;
    /* The length is essentially the size of the structure minus sizeof(mtype) */
    length = sizeof(struct messageBuffer) - sizeof(long);
    if((result = msgrcv(id, dataBuffer, length, type, 0)) == -1)
    {
        return(0);
    }
    return(1);
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
=======
    /* Read a msg from a mailslot, return nr Uses mq as reference pointer,
     * so that you can 	reach the handle from anywhere
     * of successful bytes read */

    int ret =  mq_receive(*mq, *refBuffer, MAX_SIZE, 0);
    perror("mx_receive");
    return ret;
}

int MQwrite (mqd_t * mq, char * sendBuffer)
{
    /* Write a msg to a mailslot, return nr Uses mq as reference pointer,
     * so that you can reach the handle from anywhere
    * of successful bytes written */

    int ret = mq_send(*mq, sendBuffer, MAX_SIZE, 0);
    perror("mq_send");
    return ret;

}

int MQclose(mqd_t * mq)
{
    /* close a mailslot, returning whatever the service call returns
     * Uses mq as reference pointer, so that you can
     * reach the handle from anywhere
    * Should return 1 on success and 0 on fail*/

	 return mq_close(*mq);
>>>>>>> 2b3273095f24148776cef1b86a714072220eb829
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



