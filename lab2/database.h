#ifndef DATABASE_H
#define DATABASE_H
pthread_mutex_t databaseControl;
typedef struct linkedList
{
    struct list_head list;
    planet_type* planetPointer;
} database;
database databaseHead;
#endif
