#ifndef DATABASE_H
#define DATABASE_H
#include <pthread.h>
#include "wrapper.h"
#include "list.h"

extern pthread_mutex_t databaseControl;
typedef struct linkedList
{
    struct list_head list;
    planet_type* planetPointer;
} database;
extern database databaseHead;
#endif
