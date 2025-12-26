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

float screenWidth;
float screenHeight;

sf::Font font("comicFont.ttf");


Button startBtn(font);
Button quitBtn(font);
Button optBtn(font);

sf::RenderWindow* windowPtr;



// Konstruktor MainMenuState
//Kod umieszczony poni¿ej wykona siê RAZ
MainMenuState::MainMenuState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
    this->windowPtr = windowPtr;
    
    screenHeight = windowPtr->getSize().y;
    screenWidth = windowPtr->getSize().x;



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

    startBtn.text.setString("Start");
    startBtn.SetPosition(screenWidth / 2, screenHeight / 3);
    if (startBtn.IsMouseOver(mouseX, mouseY))
        startBtn.shape.setFillColor(sf::Color::Red);
    else
        startBtn.shape.setFillColor(sf::Color::Magenta);

    optBtn.text.setString("Options");
    optBtn.SetPosition(screenWidth / 2, screenHeight / 2);
    if (optBtn.IsMouseOver(mouseX, mouseY))
        optBtn.shape.setFillColor(sf::Color::Red);
    else
        optBtn.shape.setFillColor(sf::Color::Magenta);


    quitBtn.text.setString("Exit");
    quitBtn.SetPosition(screenWidth / 2, screenHeight - screenHeight / 3);
    if (quitBtn.IsMouseOver(mouseX, mouseY))
        quitBtn.shape.setFillColor(sf::Color::Red);
    else
        quitBtn.shape.setFillColor(sf::Color::Magenta);

}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    windowPtr->clear();
    startBtn.Draw(*windowPtr);
    quitBtn.Draw(*windowPtr);
    optBtn.Draw(*windowPtr);
    windowPtr->display();

}
