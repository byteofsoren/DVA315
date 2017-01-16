#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* print_moon(){
    while(1){
        printf("Heloo moon");
        sleep(1);
    }
}

int Main(void) {
	int i;
    pthread_t thread;
    pthread_create(&thread, NULL, print_moon, NULL);
	for(i = 0; i < 10; i++) {
		printf("Hello world!\n");
		sleep(1);
	}
	return 0;
}
