#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
#include "input.h"
#define name "/test"
#define second 1000000
pthread_mutex_t p;


//Det compilerar med gcc -g wrapper.c main.c -o prog -lrt -pthread men inte med make

void* print_moon(void){
    mqd_t talker;
    MQconnect(&talker, name);
    char * data;
    while(1){
        pthread_mutex_lock(&p);
        MQread(&talker, &data);
        printf("%s\n", data);
        pthread_mutex_unlock(&p);
        usleep(100);
    }
    return NULL;
}

int main(void) {

    mqd_t talker;
    MQcreate(&talker, name);
    threadCreate(print_moon, 0);
    while(1){
        pthread_mutex_lock(&p);
        char* text;
        text = (char*)input("prompt: ");
        MQwrite(&talker, text);
        pthread_mutex_unlock(&p);
        free(text);
        usleep(100);
	}
	return 0;
}

