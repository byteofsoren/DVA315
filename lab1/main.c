#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "skelett-linux/wrapper.h"

#define second 1000000

void* print_moon(){
    int i;
    for(i = 0; i < 10; i++) {
        printf("Hello moon \n");
        usleep(0.2 * second);
    }
}

int main(void) {
	int i;
    pthread_t thread;
   while(1){
	for(i = 0; i < 10; i++) {
		printf("Hello world!\n");
		usleep(1 * second);
	}
	pthread_create(&thread, NULL, print_moon, NULL);
	pthread_join(thread, NULL);
	}
	return 0;
}
