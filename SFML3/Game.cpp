#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
#include "MainMenuState.h"
#include <vector>

// --- KONSTRUKTOR I DESTRUKTOR ---
Game::Game()
{
    this->InitWindow();
    this->InitStates();
}

Game::~Game()
{
    // Tutaj w przysz³oœci warto dodaæ czyszczenie wektora states, jeœli nie jest pusty
}

// --- INICJALIZACJA ---
void Game::InitWindow()
{
    this->windowPtr = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "B.A.N.A.I.S");
}

void Game::InitStates()
{
    // TUTAJ UMIESZCZMAY STANY CZYTAJ SCENY JEST 3.13 OCZY MI WYCHODZ¥ Z ORBIT
    states.clear();
    this->states.push_back(new MainMenuState(this->windowPtr));
    activeState = 1;
}

// --- PÊTLA G£ÓWNA I STEROWANIE ---
void Game::Run()
{
    while (this->windowPtr->isOpen()) {
        this->dt = dtClock.restart().asSeconds(); // Obliczanie czasu klatki
        this->Update(this->dt);
        this->Render();
    }
}

// --- AKTUALIZACJA LOGIKI ---
void Game::UpdateEvent()
{
    while (ev = this->windowPtr->pollEvent())
    {
        if (ev->is<sf::Event::Closed>())
            windowPtr->close();
    }
}

void Game::Update(float dt)
{
    UpdateEvent();

    if (!states.empty())
    {
        states.back()->Update(dt);

        // Mechanizm zmiany/zamykania stanów
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
        // Zamknij aplikacjê, jeœli nie ma ju¿ ¿adnych stanów
        windowPtr->close();
    }
}

// --- RENDEROWANIE ---
void Game::Render()
{
    if (!states.empty())
    {
        windowPtr->clear();
        states.back()->Render(windowPtr); // Rysuje tylko aktualny stan na wierzchu
        windowPtr->display();
    }
}

// --- IMPLEMENTACJA KLASY BAZOWEJ STATES ---
// (Te metody znajduj¹ siê w pliku Game.cpp zgodnie z Twoim kodem)
void States::CheckForQuit()
{
}

bool States::GetQuit()
{
    return quit;
}