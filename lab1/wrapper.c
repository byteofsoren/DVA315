#include "wrapper.h"
#define MAX_SIZE 1024

int MQcreate (mqd_t * mq, char * name)
{
    return 0;
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
pthread_t* threadCreate (void * functionCall, int threadParam)
{
	pthread_t* thread = (pthread_t*)calloc(sizeof(pthread_t), 1);
    int* parm = (int*)calloc(sizeof(int),1);
    *parm = threadParam;
	pthread_create(thread, NULL, functionCall, parm);
	return thread;
	//This might work, but threadParam might go out of scope before the thread is created
}



