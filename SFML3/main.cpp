#include <SFML/Graphics.hpp>
#include "Monster.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //test repo pomyœlny
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "TEST");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}