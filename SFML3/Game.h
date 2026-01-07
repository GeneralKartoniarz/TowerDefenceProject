#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "States.h"
#include "GameState.h"

#include <vector>
#include <optional>

using namespace std;

class Game
{
public:
    // --- Konstruktor i Destruktor ---
    Game();
    ~Game();

    // --- Glówne metody steruj¹ce ---
    void Run();                 // G³ówna pêtla gry (Game Loop)
    void Update(float dt);      // Aktualizacja logiki stanów
    void Render();              // Czyszczenie okna i wywo³anie rysowania stanów

    // --- Inicjalizacja ---
    void InitWindow();          // Tworzenie i konfiguracja okna SFML
    void InitStates();          // Wstêpna konfiguracja stosu stanów

    // --- Obs³uga wejœcia ---
    void UpdateEvent();         // Przetwarzanie zdarzeñ (klawiatura, mysz, okno)

private:
    // --- Okno i czas ---
    sf::RenderWindow* windowPtr; // WskaŸnik na okno aplikacji
    sf::Clock dtClock;           // Zegar do mierzenia czasu klatki
    float dt;                    // Czas delty (Delta Time)

    // --- System stanów ---
    vector<States*> states;      // Kontener przechowuj¹cy aktywne stany
    int activeState;             // Indeks aktualnie przetwarzanego stanu

    // --- Obs³uga zdarzeñ ---
    optional<sf::Event> ev;      // Obiekt przechowuj¹cy zdarzenia SFML
};