#ifdef __cplusplus
extern "C" {
#endif
#ifndef DATABASE_H
#define DATABASE_H
#include <pthread.h>
#include "wrapper.h"


extern pthread_mutex_t databaseControl;

typedef struct node
{
    planet_type *planet;
    struct node *prev_planet;
    struct node *next_planet;
} NODE;

extern NODE *databaseHead;

void addPlanet(NODE *data);

void removePlanet(NODE *data);



#ifdef __cplusplus
}
#endif
#endif
