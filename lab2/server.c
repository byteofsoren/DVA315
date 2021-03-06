#include "wrapper.h"
#include "common.h"
#include "database.h"
#include "graphics.h"
#include <math.h>
#define G 0.0000000000667259
#define dt 1000
int SERVER_RUNNING = 1;

void* planet(planet_type* myPlanet)
{
    NODE* tmp;
    tmp = (NODE*)calloc(1,sizeof(NODE));
    tmp->planet = myPlanet;
    pthread_mutex_lock(&databaseControl);
    addPlanet(tmp);
    pthread_mutex_unlock(&databaseControl);
    int messageID;
    MQcreate(&messageID, MQNAME);
    struct messageBuffer writeBuffer;
    writeBuffer.command = 1;
    writeBuffer.mtype = myPlanet->pid;
    writeBuffer.planet = *myPlanet;
    MQwrite(messageID, &writeBuffer);
    NODE* iter;
    while (myPlanet->life > 0 && SERVER_RUNNING > 0)
    {
        double ax = 0, ay = 0, r, A;
        pthread_mutex_lock(&databaseControl);
        for(iter = databaseHead; iter != NULL; iter = iter->next_planet)
        {
            if (iter->planet != myPlanet)
            {
                r = sqrt(pow(iter->planet->sx - myPlanet->sx, 2) + pow(iter->planet->sy - myPlanet->sy, 2));
                if(r < 0.001) r = 0.001;
                A = G * iter->planet->mass / pow(r, 2);
                ax += A * (iter->planet->sx - myPlanet->sx) / r;
                ay += A * (iter->planet->sy - myPlanet->sy) / r;
            }
        }
        pthread_mutex_unlock(&databaseControl);
        myPlanet->vx += ax * dt;
        myPlanet->vy += ay * dt;
        myPlanet->sx += myPlanet->vx * dt;
        myPlanet->sy += myPlanet->vy * dt;
        myPlanet->life -= 1;
        if ((abs(myPlanet->sx) > DISPH) || (abs(myPlanet->sy) > DISPW)) myPlanet->life = 0;
        usleep(10000);
    }
    pthread_mutex_lock(&databaseControl);
    removePlanet(tmp);
    pthread_mutex_unlock(&databaseControl);
    free(tmp);
    writeBuffer.command = 0;
    writeBuffer.mtype = myPlanet->pid;
    writeBuffer.planet = *myPlanet;
    MQwrite(messageID, &writeBuffer); 
    free(myPlanet);
    return (void*) NULL;
}

void* callGraphics(void)
{
    showGrapics();
    return (void*) NULL;
}

int main(void)
{
    int messageID;
    MQcreate(&messageID, MQNAME);
    struct messageBuffer readBuffer;
    threadCreate(callGraphics, NULL);
    while(SERVER_RUNNING > 0)
    {
        if(MQread(messageID, MAIN_MQ_TYPE, &readBuffer))
        {
            if(readBuffer.command == 3)
            {
                pthread_mutex_lock(&databaseControl);
                usleep(1000000 * 3);
                pthread_mutex_unlock(&databaseControl);
            }
            else if(readBuffer.command == 0)
            {
                SERVER_RUNNING = readBuffer.command;
            }
            else
            {
                planet_type* newPlanet = (planet_type*)calloc(1, sizeof(planet_type));
                *newPlanet = readBuffer.planet;
                threadCreate(planet, newPlanet);
            }
        }
    }
    MQclose(messageID);
    usleep(100000);
}
