#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"

#define second 1000000

void* print_moon(void * arg){
    int i;
    int *threadParam;
    threadParam =  (int*)arg;
    for(i = 0; i < 10; i++) {
        printf("Hello moon id=%d\n", *threadParam);
        usleep(0.2 * second);
    }
    return NULL;
}

int main(void) {
    int i;
    while(1){
        for(i = 0; i < 10; i++) {
            printf("Hello world!\n");
            usleep(1 * second);
        }
        pthread_t* thr;
        thr = threadCreate(print_moon, 1);
        pthread_join(*thr, NULL);
	}
	return 0;
}

