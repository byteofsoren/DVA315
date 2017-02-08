#ifdef __cplusplus
extern "C" {
#endif
#ifndef DATABASE_H
#define DATABASE_H
#include <pthread.h>
#include "wrapper.h"
//#include "list.h"

extern pthread_mutex_t databaseControl;


typedef struct node
{
    planet_type *planet;
    struct node *prev_planet;
    struct node *next_planet;
} NODE;

NODE *DB;

void createDatabase(NODE data);
void addPlanet(DB data, planet_type *planet);
planet_type *getPlanet(DB data, int pid);
void removePlanet(DB data, int pid);



#ifdef __cplusplus
}
#endif
#endif
