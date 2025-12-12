//SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//Klasy
#include "Monster.h"
#include "Tower.h"
//Funkcjonalnoœci
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //test repo pomyœlny
    
    //Tworzenie okna gry
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