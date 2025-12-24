#include "MainMenuState.h"
#include "States.h"      
#include "Button.h"      
#include <iostream>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;


float mouseX;
float mouseY;

sf::Font font("comicFont.ttf");


Button startBtn(font);

sf::RenderWindow* windowPtr;



// Konstruktor MainMenuState
//Kod umieszczony poni¿ej wykona siê RAZ
MainMenuState::MainMenuState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
    windowPtr = this->windowPtr;
    
}

// Destruktor GameState
MainMenuState::~MainMenuState() {

}
// Funkcja wywo³ywana przy koñczeniu stanu
void MainMenuState::EndState()
{

}

// Sprawdza, czy stan powinien zostaæ zakoñczony
void MainMenuState::QuitCheck()
{
    this->CheckForQuit();
}

// G³ówna funkcja logiki stanu gry
// dt = delta time (czas jednej klatki)
//Kod w tej funkcji wykona siê CO KLATKE
void MainMenuState::Update(float dt)
{
    this->QuitCheck();
    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;


}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    startBtn.Draw(*windowPtr);

}
