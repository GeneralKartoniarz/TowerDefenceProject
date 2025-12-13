#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
#include "MainMenuState.h"
Game::Game()
{
	this->InitWindow();
    this->InitStates();
}

Game::~Game()
{
    while (!state.empty()) {
        delete state.top();
        state.pop();
    }

    delete windowPtr;

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

void Game::Update(float dt)
{
    this->UpdateEvent();
    if(!this->state.empty()) {
        this->state.top()->Update(dt);
    }
    if (state.top()->GetQuit()) {
        delete state.top();
        state.pop();
    }
    //zamykanie gry
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
        this->dt = dtClock.restart().asSeconds();
        this->Update(this ->dt);
        this->Render();
    }
}

void Game::InitStates()
{
    //TUTAJ UMIESZCZMAY STANY CZYTAJ SCENY JEST 3.13 OCZY MI WYCHODZ¥ Z ORBIT
    this->state.push(new GameState(this->windowPtr));
    this->state.push(new MainMenuState(this->windowPtr));

}

