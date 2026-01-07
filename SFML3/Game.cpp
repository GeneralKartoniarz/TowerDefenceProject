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
    //Test
	this->InitWindow();
    this->InitStates();
}

Game::~Game()
{

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

}

bool States::GetQuit()
{
    return quit;
}

void Game::Update(float dt)
{
    UpdateEvent();

    if (!states.empty())
    {
        states.back()->Update(dt);

        if (states.back()->GetQuit())
        {
            States* next = states.back()->nextState;

            delete states.back();
            states.pop_back();

            if (next)
                states.push_back(next);
        }
    }
    else
    {
        windowPtr->close();
    }

}

void Game::Render()
{
    if (!states.empty())
    {
        windowPtr->clear();
        states.back()->Render(windowPtr);
        windowPtr->display();
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
    states.clear();
    this->states.push_back(new MainMenuState(this->windowPtr));
    activeState = 1;

}

