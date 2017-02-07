#ifndef WRAPPER_H
#define WRAPPER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>


// Mailslot handling:
extern int threadCreate (void * functionCall, int threadParam);


struct messageBuffer {
    long mtype;
    planet_type planet; 
   
};

extern int MQcreate (int * id,char * name);
extern int MQconnect (int * id, char * name);
extern int MQread (int id, long type, struct messageBuffer *dataBuffer);
extern int MQwrite (int id, struct messageBuffer *dataBuffer);
extern int MQclose (int id);



// Struct for planet data will be used in lab 2 and 3 !!!!!
// Just ignore in lab1 or you can try to send it on your mailslot, 
// will be done in lab 2 and 3

typedef struct pt {
	char		name[20];	// Name of planet
	double		sx;			// X-axis position
	double		sy;			// Y-axis position
	double		vx;			// X-axis velocity
	double		vy;			// Y-axis velocity
	double		mass;		// Planet mass
	int			life;		// Planet life
	int		    pid;	    // ID of creating process
} planet_type;

#endif /* WRAPPER_H */
