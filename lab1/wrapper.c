#include "wrapper.h"

#define MAX_SIZE 1024

int MQcreate (mqd_t * mq, char * name)
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    *mq = mq_open(name, O_CREAT | O_RDONLY, 0644, &attr);
    return (mqd_t)-1 != *mq;
}
int MQconnect (mqd_t * mq, char * name)
{
    return 0;
}

int MQread (mqd_t * mq, char ** refBuffer)
{
    return 0;
}

int MQwrite (mqd_t * mq, char * sendBuffer)
{
    return 0;
}

int MQclose(mqd_t * mq, char * name)
{
    return 0;
}
int threadCreate (void * functionCall, int threadParam)
{
	pthread_t thread;
    int* par = (void *)calloc(sizeof(int), 1);
    *par = threadParam;  
	return pthread_create(&thread, NULL, functionCall, par);
}



