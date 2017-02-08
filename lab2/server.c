#include "wrapper.h"
#include "common.h"
#include "database.h"
#include <math.h>
#define G 0.0000000000667259
#define dt 1

pthread_mutex_t databaseControl;
database databaseHead;

void* planet(planet_type* myPlanet)
{
    database* tmp;
    tmp = (database*)calloc(1,sizeof(database));
    tmp->planetPointer = myPlanet;
    pthread_mutex_lock(&databaseControl);
    list_add_tail(&(tmp->list), &(databaseHead.list));
    pthread_mutex_unlock(&databaseControl);
    database* iter;
    while (myPlanet->life > 0)
    {
        double ax = 0, ay = 0, r, A;
        pthread_mutex_lock(&databaseControl);
        list_for_each_entry(iter, &databaseHead.list, list)
        {
            if (iter->planetPointer != myPlanet)
            {
                r = sqrt(pow(iter->planetPointer->sx - myPlanet->sx, 2) + pow(iter->planetPointer->sy - myPlanet->sy, 2));
                A = G * iter->planetPointer->mass / pow(r, 2);
                ax += A * (iter->planetPointer->sx - myPlanet->sx) / r;
                ay += A * (iter->planetPointer->sy - myPlanet->sy) / r;
            }
        }
        pthread_mutex_unlock(&databaseControl);
        myPlanet->vx += ax * dt;
        myPlanet->vy += ay * dt;
        myPlanet->sx += myPlanet->vx * dt;
        myPlanet->sy += myPlanet->vy * dt;
        myPlanet->life -= 1;
        if ((myPlanet->sx < 0) || (myPlanet->sx > DISPH) || (myPlanet->sy < 0) || (myPlanet->sy > DISPW)) myPlanet->life = 0;
        usleep(10000);
    }
    pthread_mutex_lock(&databaseControl);
    list_del(&tmp->list);
    free(tmp);
    //Send data that planet is dead
    free(myPlanet);
    return (void*) NULL;
}
