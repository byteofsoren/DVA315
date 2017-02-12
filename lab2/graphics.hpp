#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <SFML/Graphics.hpp>
extern "C" {
#include "common.h"
#include "wrapper.h"
}


class Graphics
{
private:
    int width; int height;
    int running;
    sf::RenderWindow window;
    sf::Event event;

public:
    Graphics(int width, int height);
    virtual ~Graphics();
    void update();
    void clear();
    int isOpen();
    int addPlanet(planet_type *pl);
    void clearPlanets();

};

#endif /* GRAPHICS_H */
