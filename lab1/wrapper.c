#include "wrapper.h"
#include <errno.h>


int MQcreate (mqd_t * mq, char * name)
{
    /* Creates a mailslot with the specified name. Uses mq as reference
     * pointer, so that you can reach the handle from anywhere
     * Should be able to handle a messages of any size
     * Should return 1 on success and 0 on fail*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_CREAT | O_RDWR, &attr);
    return (mqd_t)-1 != *mq;
}
int MQconnect (mqd_t * mq, char * name)
{
    /* Connects to an existing mailslot for writing Uses mq as reference pointer,
     * so that you can 	reach the handle from anywhere
     * Should return 1 on success and 0 on fail*/
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_RDWR, &attr);
    //perror("mq_open");
    return (mqd_t)-1 != *mq;
}

int MQread (mqd_t * mq, char ** refBuffer)
{
    /* Read a msg from a mailslot, return nr Uses mq as reference pointer,
     * so that you can 	reach the handle from anywhere
     * of successful bytes read */
    int error = 0;
    for (int i = 0; i < MAX_MESSAGES; ++i) {
        int Merror = mq_receive(*mq, refBuffer[i], MAX_SIZE - 1, 0);
        perror("mq_receive");
        if (Merror == -1){
            error = -1;
            break;
        }
    }
//    int ret =  mq_receive(*mq, *refBuffer, MAX_SIZE - 10, 0);
    return error;
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

int MQclose(mqd_t * mq, const char *name)
{
    /* close a mailslot, returning whatever the service call returns
     * Uses mq as reference pointer, so that you can
     * reach the handle from anywhere
    * Should return 1 on success and 0 on fail*/
    int error_close = 0 , error_unlink = 0;
	error_close = mq_close(*mq);
    error_unlink = mq_unlink(name);
    if ((error_close == -1) | (error_unlink == -1)) {
        return -1;
    }else{
        return 0;
    }
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



