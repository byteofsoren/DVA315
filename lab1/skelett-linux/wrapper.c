#include "wrapper.h"
#define MAX_SIZE 1024

int MQcreate (mqd_t * mq, char * name)
{
}
int MQconnect (mqd_t * mq, char * name)
{
}

int MQread (mqd_t * mq, char ** refBuffer)
{
}

int MQwrite (mqd_t * mq, char * sendBuffer)
{
}

int MQclose(mqd_t * mq, char * name)
{
}
int threadCreate (void * functionCall, int threadParam)
{
	pthread_t thread;
	return pthread_create(&thread, NULL, functionCall, &threadParam);

	//This might work, but threadParam might go out of scope before the thread is created
}



