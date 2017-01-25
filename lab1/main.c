#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
#include "input.h"
#define NAME "/test"
#define second 1000000
pthread_mutex_t p;




<<<<<<< HEAD
void* print_moon(void * arg){
    struct messageBuffer buf;
    buf.mtype = 1;
    int id;
    MQcreate(&id, NAME);   
=======
void* print_moon(void){
    mqd_t talker;
    MQconnect(&talker, name);
    char * data;
>>>>>>> 2b3273095f24148776cef1b86a714072220eb829
    while(1){
        pthread_mutex_lock(&p);
        MQread(id, 1, &buf);
        printf("%s\n", buf.data);
        pthread_mutex_unlock(&p);
        usleep(100);
    }
    return NULL;
}

int main(void) {
    struct messageBuffer buf;
    buf.mtype = 1;
    int id;
    MQcreate(&id, NAME);
    threadCreate(print_moon, 0);
    buf.data = (char*)calloc(1,1);
    while(1){
        pthread_mutex_lock(&p);
<<<<<<< HEAD
        free(buf.data);
        buf.data = (char*)input("prompt: ");
        MQwrite(id, &buf);
=======
        char* text;
        text = (char*)input("prompt: ");
        MQwrite(&talker, text);
>>>>>>> 2b3273095f24148776cef1b86a714072220eb829
        pthread_mutex_unlock(&p);
        free(text);
        usleep(100);
	}
	return 0;
}

