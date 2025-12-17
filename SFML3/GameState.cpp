#include "GameState.h"   
#include "States.h"      
#include <iostream>      

using namespace std;  



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
}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void GameState::Render(sf::RenderWindow* windowPtr)
{
}
