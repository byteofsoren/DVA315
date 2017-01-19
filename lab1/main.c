#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"

#define second 1000000
pthread_mutex_t p;

void* print_moon(void * arg){
    int i;
    while(1){
     
        pthread_mutex_lock(&p);
        for(i = 0; i < 10; i++) {
            printf("Hello moon\n");
            usleep(0.2 * second);
        }
        pthread_mutex_unlock(&p);
        usleep(0);
    }
    return NULL;
}

int main(void) {
    int i;

    threadCreate(print_moon, 0);
    while(1){
        pthread_mutex_lock(&p);
        for(i = 0; i < 10; i++) {
            printf("Hello world!\n");
            usleep(1 * second);
        }
        pthread_mutex_unlock(&p);
        usleep(0);
	}
	return 0;
}

