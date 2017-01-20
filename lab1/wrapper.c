#include "wrapper.h"

#define MAX_SIZE 1024

int MQcreate (mqd_t * mq, char * name)
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_CREAT | O_RDWR, &attr);
    return (mqd_t)-1 != *mq;
}
int MQconnect (mqd_t * mq, char * name)
{
    struct mq_attr attr;
     attr.mq_flags = 0;
     attr.mq_maxmsg = 10;
     attr.mq_msgsize = MAX_SIZE;
     attr.mq_curmsgs = 0;
     *mq = mq_open(name, O_RDWR, &attr);
     return (mqd_t)-1 != *mq;
}

int MQread (mqd_t * mq, char ** refBuffer)
{
    return mq_receive(*mq, *refBuffer, MAX_SIZE, 0);
}

int MQwrite (mqd_t * mq, char * sendBuffer)
{   
    return mq_send(*mq, sendBuffer, MAX_SIZE, 0);

}

int MQclose(mqd_t * mq, char * name)
{
 return mq_close(*mq);
}
int threadCreate (void * functionCall, int threadParam)
{
	pthread_t thread;
    int* par = (void *)calloc(sizeof(int), 1);
    *par = threadParam;  
	return pthread_create(&thread, NULL, functionCall, par);
}



