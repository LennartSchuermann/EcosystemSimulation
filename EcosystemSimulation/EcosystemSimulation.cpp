#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.h"
#include "Entity.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENSIZE[0], SCREENSIZE[1]), "Ecosystem by Lennart S.", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(FPS);

    //Game clock
    sf::Clock clock;

    std::vector<Entity> entities;
    //max Test: 10.000
    for (int i = 0; i < 500; i++) 
    {
        Entity entity;
        entities.push_back(entity);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        float time = clock.restart().asSeconds();
        float fps = 1.0f / time;

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //Update stuff...
        for (auto& entity : entities) {
            entity.Update();
        }

        // clear the window with black color
        window.clear(sf::Color(61, 61, 61));

        //Draw stuff...
        for (auto& entity : entities) {
            window.draw(entity.getCollisionShape());
            window.draw(entity.getShape());
        }

        // end the current frame
        window.display();
    }

    return 0;
}