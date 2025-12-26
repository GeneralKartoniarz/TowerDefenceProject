#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
#include "MainMenuState.h"
#include <vector>
Game::Game()
{
	this->InitWindow();
    this->InitStates();
}

Game::~Game()
{
    for (auto* s : state)
        delete s;
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
        this->state[activeState]->Update(dt);
    }
    if (state[activeState]->GetQuit()) {
        state[activeState]->quit = false;
        activeState = (activeState + 1) % state.size();
    }
    //zamykanie gry
    if (state.empty()) {
        windowPtr->close();
    }

}

void Game::Render()
{
    if(!this->state.empty()) {
        this->state[activeState]->windowPtr->clear();
        state[activeState]->Render(windowPtr);
        this->state[activeState]->windowPtr->display();
    }
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
    this->state.push_back(new GameState(this->windowPtr));
    this->state.push_back(new MainMenuState(this->windowPtr));
    activeState = 1;

}

