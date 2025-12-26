#include "GameState.h"   
#include "States.h"           
#include "Button.h"      
#include <iostream>   
#include <string>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;  




sf::Font fontGameState("comicFont.ttf");


// Konstruktor GameState
//Kod umieszczony poni¿ej wykona siê RAZ
GameState::GameState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
}

// Destruktor GameState
GameState::~GameState() {

}

void GameState::EndState() {

}
// Sprawdza, czy stan powinien zostaæ zakoñczony
void GameState::QuitCheck()
{
    this->CheckForQuit();
}

// G³ówna funkcja logiki stanu gry
// dt = delta time (czas jednej klatki)
//Kod w tej funkcji wykona siê CO KLATKE
void GameState::Update(float dt)
{
    this->QuitCheck();

    float screenWidth;
    float screenHeight;

    screenHeight = windowPtr->getSize().y;
    screenWidth = windowPtr->getSize().x;

    float mouseX;
    float mouseY;

    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;
    
}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void GameState::Render(sf::RenderWindow* windowPtr)
{
}
