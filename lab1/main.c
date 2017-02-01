#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
#include "input.h"
#define NAME "test"
#define second 1000000
pthread_mutex_t p;




//function used as thread, printing data sent over the message queue.
void* print_moon(void * arg){
    struct messageBuffer buf;
    buf.mtype = 1;
    buf.run = 1;
    int id;
    while(buf.run){
        pthread_mutex_lock(&p);
        MQcreate(&id, NAME);
        MQread(id, 1, &buf);

        printf("%s\n", buf.data);
        MQclose(id);
        pthread_mutex_unlock(&p);
        usleep(100);
    }
    return NULL;
}

//main thread, taking userinput, sending over the message queue.
int main(void) {
    struct messageBuffer buf;
    buf.mtype = 1;
    buf.run = 1;
    int id;
    threadCreate(print_moon, 0);
    buf.data = (char*)calloc(1,1);
    while(buf.run){
        pthread_mutex_lock(&p);
        free(buf.data);
        buf.data = (char*)input("prompt: ");
        if(!strcmp(buf.data, "END")) buf.run = 0;
        MQcreate(&id, NAME);
        MQwrite(id, &buf);
        pthread_mutex_unlock(&p);
        usleep(100);
	}
	return 0;
}

