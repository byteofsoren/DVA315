#ifndef WRAPPER_H
#define WRAPPER_H




// Mailslot handling:
extern int threadCreate (void * functionCall, int threadParam);

extern int initSocket (int * socketHandle);
extern int socketConnect (int * socketHandle);

extern int mailslotWrite (int * socketHandle, void * msg, int msgSize);
extern int mailslotRead (int * socketHandle, void * msg, int msgSize);

extern int socketClose (int * socketHandle);


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
	struct pt*	next;		// Pointer to next planet in linked list
	int			life;		// Planet life
	char		pid[30];	// String containing ID of creating process
} planet_type;

#endif /* WRAPPER_H */
