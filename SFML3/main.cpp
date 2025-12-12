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
    //zmienne lokalne
    float windowWidth = 1920.0f;
    float windowHeight = 1080.0f;
    
    //Tworzenie okna gry
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "TEST", sf::Style::Titlebar | sf::Style::Close);


    //G³ówna pêtla gry
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::White);
        window.display();
    }
}