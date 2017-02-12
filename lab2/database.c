#include "database.h"

pthread_mutex_t databaseControl;
NODE *databaseHead = NULL;

void addPlanet(NODE *data)
{
    data->next_planet = databaseHead;
    data->prev_planet = NULL;
    databaseHead = data;
}

void removePlanet(NODE *data)
{
    if (data->next_planet != NULL && data->prev_planet != NULL)
    {
        data->next_planet->prev_planet = data->prev_planet;
        data->prev_planet->next_planet = data->next_planet;
    }
    else if (data->next_planet == NULL && data->prev_planet == NULL)
    {
        databaseHead = NULL;
    }
    else if (data->next_planet == NULL)
    {
        data->prev_planet->next_planet = NULL;
    }
    else
    {
        databaseHead = data->next_planet;
        data->next_planet->prev_planet = NULL;
    }
}
