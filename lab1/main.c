#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "wrapper.h"
#include "input.h"
#define name "/test3"
#define second 1000000
pthread_mutex_t p;


//Det compilerar med gcc -g wrapper.c main.c -o prog -lrt -pthread men inte med make

void* print_moon(void){
    mqd_t talker;
    MQconnect(&talker, name);
    char **data;
    *data = (char*)calloc(sizeof(char*), MAX_MESSAGES);
    for (int i = 0; i < MAX_MESSAGES; ++i) {
        data = (char)calloc(sizeof(char), MAX_SIZE + 50);
    }
    while(1) {
        //data = (char*)memset(data, 0, MAX_SIZE + 50);
        pthread_mutex_lock(&p);
        MQread(&talker, data);
        //printf("%s\n", data);
        pthread_mutex_unlock(&p);
        usleep(100);
    }
}

int main(void) {
    int run = 1;
    mqd_t talker;
    MQcreate(&talker, name);
    threadCreate(print_moon, 0);
    while(run){
        pthread_mutex_lock(&p);
        char* text;
        text = (char*)input("prompt: ");
        if (strcmp( text, "exit") == 0) {
            run = 0;
            break;
        }
        MQwrite(&talker, text);
        pthread_mutex_unlock(&p);
        free(text);
        usleep(100);
	}
    MQclose(&talker, name);
	return 0;
}

