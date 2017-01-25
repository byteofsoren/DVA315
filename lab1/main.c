#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
//#include "input.h"
#define NAME "test"
#define second 1000000
pthread_mutex_t p;





void* print_moon(void * arg){
    struct messageBuffer buf;
    buf.mtype = 1;
    int id;
    while(1){
        pthread_mutex_lock(&p);
        MQcreate(&id, NAME);
        MQread(id, 1, &buf);
        printf("%s %d\n", buf.data, buf.num);
        MQclose(id);
        pthread_mutex_unlock(&p);
        usleep(100);
    }
    return NULL;
}

int main(void) {
    struct messageBuffer buf;
    buf.mtype = 1;
    buf.num = 0;
    buf.data = "HELLO!";
    int id;
    threadCreate(print_moon, 0);
    //buf.data = (char*)calloc(1,1);
    while(1){
        pthread_mutex_lock(&p);
        MQcreate(&id, NAME);
        //free(buf.data);
        //buf.data = (char*)input("prompt: ");
        buf.num += 1;
        MQwrite(id, &buf);
        pthread_mutex_unlock(&p);
        usleep(100);
	}
	return 0;
}

