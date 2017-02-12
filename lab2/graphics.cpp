
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "graphics.hpp"
#include "graphics.h"
#include "database.h"

#define FRAMEUPDATETIMER 10000 //Microseconds, increase value for slower update time


Graphics::Graphics(int width, int height)
{
    Graphics::height = height;
    Graphics::width = width;
    window.create(sf::VideoMode(width,height), "Orbital system");
    //sf::VideoMode(800, 800), "Orbital system");
   // window.clear();
}

Graphics::~Graphics(){
    window.close();
}

void Graphics::clear(){
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            //Graphics::~Graphics();
        }
    }
    window.clear();

}

void Graphics::update()
{
    window.display();
}

int  Graphics::isOpen()
{
    return window.isOpen();
}


int Graphics::addPlanet(planet_type *pl)
{
    // Adds planet to the vector so it renders.
    sf::CircleShape gplanet(pl->mass*0.1);
    sf::Vector2u size = window.getSize();
    gplanet.setPosition(pl->sx + size.x/2, pl->sy + size.y/2);
    gplanet.setFillColor(sf::Color::Green);
    window.draw(gplanet);
    return 0;
}

void showGrapics(void){
    Graphics *plot = new Graphics(DISPW, DISPH);
    // Read the data from the databese.
    plot->isOpen();
    while(plot->isOpen()){//}
        // Running while the client is open.
        plot->clear();
        // add planets to the screen
        pthread_mutex_lock(&databaseControl);       // first lock the mutex
        NODE* iter;                                 // pointer to iterate the planets.
        for (iter = databaseHead; iter !=  NULL ; iter = iter->next_planet) {
            plot->addPlanet(iter->planet);
        }
        pthread_mutex_unlock(&databaseControl);     // Un lock the mutex.
        plot->update();
        usleep(FRAMEUPDATETIMER);
    }
}


