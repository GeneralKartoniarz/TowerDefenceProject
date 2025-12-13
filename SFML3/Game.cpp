#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
Game::Game()
{
	this->InitWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::InitWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({1920,1080}), "TEST");
}

void Game::UpdateEvent()
{
    while (this->window->isOpen())
    {

        while (ev = this->window->pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                this->window->close();
        }
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
}

void Game::Render()
{
    this->window->clear();
    this->window->display();
}

void Game::Run()
{
    while (this->window->isOpen()) {
        this->Update();
        this->Render();
    }
}
