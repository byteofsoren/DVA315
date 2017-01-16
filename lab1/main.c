#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* print_moon(){
    int n = 0;
    while(1){
        printf("Hello moon %d\n", n);
	n++;
        usleep(200);
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
