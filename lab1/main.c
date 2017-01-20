#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
#include "input.h"
#define name "/test"
#define second 1000000
pthread_mutex_t p;


//Det compilerar med gcc -g wrapper.c main.c -o prog -lrt -pthread men inte med make

void* print_moon(void * arg){
    int i;
    while(1){
        pthread_mutex_lock(&p);
        for(i = 0; i < 10; i++) {
            printf("Hello moon\n");
            usleep(0.2 * second);
        }
        pthread_mutex_unlock(&p);
        usleep(100);
    }
    return NULL;
}

int main(void) {
    int i;
    mqd_t talker;
    MQcreate(&talker, name);
    threadCreate(print_moon, 0);
    while(1){
        pthread_mutex_lock(&p);
        for(i = 0; i < 10; i++) {
            char* text;
            text = (char*)input("prompt: ");
            //printf("Enterd text %s\n", text);
            //usleep(1 * second);
        }
        pthread_mutex_unlock(&p);
        usleep(100);
	}
	return 0;
}

