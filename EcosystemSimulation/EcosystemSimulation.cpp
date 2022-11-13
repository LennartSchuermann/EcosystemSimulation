#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Entity.h"

const int cells = 400;  //max Test: 1.000, Best: 400

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREENSIZE[0], SCREENSIZE[1]), "Ecosystem by Lennart S.", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(FPS);

    int childrenAmount = 0;

    //Game clock
    sf::Clock clock;
    sf::Clock runTimeclock;

    std::vector<Entity> entities;
    for (int i = 0; i < cells; i++)       
    {
        Entity entity;
        entities.push_back(entity);
    }

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time runtime = runTimeclock.getElapsedTime();

        float time = clock.restart().asSeconds();
        float fps = 1.0f / time;

        std::cout << "FPS: " << fps << std::endl;

        if (entities.size() <= 0) {
            std::cout << "-----------------------------Stats-----------------------------" << std::endl;
            std::cout << "Initial Cells: " << cells << " | Children: " << childrenAmount 
                << " \n=> " << cells + childrenAmount << std::endl;
            std::cout << "Runtime: " << runtime.asSeconds() << "s" << std::endl;
            std::cout << "---------------------------------------------------------------" << std::endl;

            window.close();
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //----------------------------------------------------------------

        //Update stuff...
        for (auto& entity:entities) {
            //TODO Sweep & Prune
            entity.Update();
            entity.HandleEntityCollision(entities, childrenAmount);
        }

        //update lifetime
        for (auto it = entities.begin(); it != entities.end(); ++it) {
            if (it->dna.currentLifeTime >= it->dna.maxAge) {
                entities.erase(it);
                break;
            }
        }

        // clear the window with dark color
        window.clear(sf::Color(61, 61, 61));

        //Draw stuff...
        for (const auto& entity : entities) {
            window.draw(entity.getCollisionShape());
            window.draw(entity.getShape());
        }

        // end the current frame
        window.display();

        //----------------------------------------------------------------
    }

    std::getchar();
    return 0;
}