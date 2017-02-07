
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "wrapper.h"


#define FRAMEUPDATETIMER 10000 //Microseconds, increase value for slower update time


{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Orbital system");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    float x = 0.0;
    float y = 0.0;

    while (window.isOpen())
    {
	//Dont remove!
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
	//Dont remove!
	shape.setPosition(x, y);
        window.clear();
        window.draw(shape);
        window.display();
	x++;
	y++;
	usleep(FRAMEUPDATETIMER);
	fflush(stdout);
	printf("Debug");
    }


    return 0;
}
