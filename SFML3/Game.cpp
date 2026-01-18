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
    // Inicjalizacja komponentów bazowych przy starcie aplikacji
    this->InitWindow();
    this->InitStates();
}

Game::~Game()
{
    // Zwalnianie zasobów dynamicznie alokowanych stanów
    for (auto* state : states)
    {
        delete state;
    }

    // Zwalnianie pamiêci okna
    delete this->windowPtr;
}

void Game::InitWindow()
{
    // Tworzenie kontekstu renderowania z okreœlon¹ rozdzielczoœci¹ i tytu³em
    this->windowPtr = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "B.A.N.A.I.S");
}

void Game::InitStates()
{
    // Konfiguracja pocz¹tkowej sceny aplikacji
    states.clear();
    this->states.push_back(new MainMenuState(this->windowPtr, false));
    activeState = 1;
}

void Game::Run()
{
    // G³ówna pêtla steruj¹ca przep³ywem aplikacji
    while (this->windowPtr->isOpen()) {
        // Obliczanie czasu up³ywaj¹cego miêdzy klatkami dla p³ynnoœci animacji
        this->dt = dtClock.restart().asSeconds();

        this->Update(this->dt);
        this->Render();
    }
}

void Game::UpdateEvent()
{
    // Obs³uga komunikatów przesy³anych przez system operacyjny
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
        // Przekazanie logiki do aktualnie aktywnego stanu na szczycie stosu
        states.back()->Update(dt);

        // Obs³uga mechanizmu przejœæ miêdzy stanami (np. wyjœcie do menu, start gry)
        if (states.back()->GetQuit())
        {
            States* next = states.back()->nextState;

            delete states.back(); // Sprz¹tanie pamiêci po zamykanym stanie
            states.pop_back();

            if (next)
                states.push_back(next); // Aktywacja nowego stanu, jeœli zosta³ zdefiniowany
        }
    }
    else
    {
        // Wyjœcie z aplikacji w przypadku braku aktywnych scen
        windowPtr->close();
    }
}

void Game::Render()
{
    if (!states.empty())
    {
        windowPtr->clear();

        // Delegacja procesu rysowania do bie¿¹cego stanu
        states.back()->Render(windowPtr);

        windowPtr->display();
    }
}
