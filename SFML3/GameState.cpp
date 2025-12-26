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


Button test(fontGameState);


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
    float screenWidth;
    float screenHeight;
    screenHeight = windowPtr->getSize().y;
    screenWidth = windowPtr->getSize().x;

    float mouseX;
    float mouseY;
    this->QuitCheck();
    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;
    string tt = to_string(mouseX) + ", " + to_string(mouseY);
    test.text.setString(tt);
    test.SetPosition(screenWidth / 2, screenHeight / 3);
    test.shape.setFillColor(sf::Color::Red);
    
}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void GameState::Render(sf::RenderWindow* windowPtr)
{
    test.Draw(*windowPtr);
}
