#include "GameState.h"
#include "States.h"
#include <iostream>
using namespace std;
GameState::GameState(sf::RenderWindow* windowPtr):States(windowPtr) {
	
}
GameState::~GameState(){

}
void GameState::EndState()
{
	cout << "chuj";
}
void GameState::QuitCheck()
{
	this->CheckForQuit();
}
void GameState::Update(float dt){
	this->QuitCheck();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		cout << "chuj";
}
void GameState::Render(sf::RenderWindow* windowPtr) {

}