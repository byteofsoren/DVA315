
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "wrapper.h"
#include "graphics.hpp"
#include "list.h"
#include "database.h"
#include "common.h"

#define FRAMEUPDATETIMER 10000 //Microseconds, increase value for slower update time
void *showGrapics(void){
    Graphics *plot = new Graphics(DISPW, DISPH);
    // Read the data from the databese.
    while(plot->isOpen()){
        // Running while the client is open.
        plot->clear();
        // add planets to the screen
        database *iter;
        list_for_each_entry(iter,&databaseHead.list, list){
            plot->addPlanet(iter->planetPointer);
        }
        plot->update();
    }

}

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
            Graphics::~Graphics();
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
    sf::CircleShape gplanet(50);
    gplanet.setPosition(pl->sx, pl->sy);
    gplanet.setFillColor(sf::Color::Green);
    window.draw(gplanet);
    return 0;
}

