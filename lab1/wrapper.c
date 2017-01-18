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
int threadCreate (void * functionCall, int threadParam)
{
	pthread_t thread;
	return pthread_create(&thread, NULL, functionCall, &threadParam);

	//This might work, but threadParam might go out of scope before the thread is created
}



