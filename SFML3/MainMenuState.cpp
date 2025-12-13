#include "MainMenuState.h"
#include "States.h"      
#include <iostream>   

using namespace std;

// Konstruktor MainMenuState
//Kod umieszczony poni¿ej wykona siê RAZ
MainMenuState::MainMenuState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{

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
}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
}
