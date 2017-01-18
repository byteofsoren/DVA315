#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"

#define second 1000000

void* print_moon(){
    int i;
    for(i = 0; i < 10; i++) {
        printf("Hello moon \n");
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
    size_t ext;
    ext = threadCreate(print_moon, 1);
    printf("suxsessfull %ld ", ext);
	}
	return 0;
}

