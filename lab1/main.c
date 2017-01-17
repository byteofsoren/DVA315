#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* print_moon(){
    int i;
    for(i = 0; i < 10; i++) {
        printf("Hello moon \n");
        usleep(200);
    }
}

int main(void) {
	int i;
    pthread_t thread;
   while(1){
	for(i = 0; i < 10; i++) {
		printf("Hello world!\n");
		sleep(1);
	}
	pthread_create(&thread, NULL, print_moon, NULL);
	pthread_join(thread, NULL);
	}
	return 0;
}
