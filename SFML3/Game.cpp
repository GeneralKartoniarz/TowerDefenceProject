#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
Game::Game()
{
	this->InitWindow();
    this->InitStates();
}

Game::~Game()
{
	delete this->windowPtr;
    if(!this->state.empty()) {
        delete this->state.top();
        this->state.pop();
    }

}

void Game::InitWindow()
{
	this->windowPtr = new sf::RenderWindow(sf::VideoMode({1920,1080}), "TEST");
}

void Game::UpdateEvent()
{
    while (ev = this->windowPtr->pollEvent())
    {
        if (ev->is<sf::Event::Closed>())
            windowPtr->close();
    }
}

void States::CheckForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        this->quit = true;
    }
}

bool States::GetQuit()
{
    return quit;
}

void Game::Update()
{
    this->UpdateEvent();
    if(!this->state.empty()) {
        this->state.top()->Update();
    }
    if (state.top()->GetQuit()) {
        delete state.top();
        state.pop();
    }
    if (state.empty()) {
        windowPtr->close();
    }
}

void Game::Render()
{
    this->windowPtr->clear();
    if(!this->state.empty()) {
        this->state.top()->Render(this->windowPtr);
    }
    this->windowPtr->display();
}

void Game::Run()
{
    while (this->windowPtr->isOpen()) {
        this->Update();
        this->Render();
    }
}

void Game::InitStates()
{
    this->state.push(new GameState(this->windowPtr));
}
void Game::ChangeState(States* newState)
{
    if (!state.empty()) {
        delete state.top();
        state.pop();
    }
    state.push(newState);
}

void Game::PushState(States* newState)
{
    state.push(newState);
}

void Game::PopState()
{
    if (!state.empty()) {
        delete state.top();
        state.pop();
    }

    if (state.empty()) {
        windowPtr->close();
    }
}

