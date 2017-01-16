#include <pthread.h>
#include <stdio.h>




int main(void) {
	int i;
	for(i = 0; i < 10; i++) {
		printf("Hello world!\n");
		sleep(1);
	}
	return 0;
}
