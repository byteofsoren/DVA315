#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
extern "C" {
#include "common.h"
#include "wrapper.h"
#include "database.h"
}
extern "C" void *showGrapics(void); // This is a thread create functinon to show the plotter.

class Graphics
{
private:
    int width; int height;
    int running;
    sf::RenderWindow window;
    sf::Event event;
    //database *data;
    //std::vector<planet_type> *planets;

public:
    Graphics(int width, int height);
    virtual ~Graphics();
    void update();
    void clear();
    int isOpen();
//    int addPlanet(planet_type *pl);
    void clearPlanets();

};

#endif /* GRAPHICS_H */
