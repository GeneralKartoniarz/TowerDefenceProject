#pragma once

// Biblioteki SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// Biblioteki standardowe
#include <iostream>
#include <stack>
#include <string>

class States
{
public:
    // --- Konstruktor i Destruktor ---
    States(sf::RenderWindow* windowPtr);
    virtual ~States();

    // --- Zarzπdzanie Stanami ---
    States* nextState = nullptr;      // Wskaünik na kolejny stan do za≥adowania
    sf::RenderWindow* windowPtr;      // Wskaünik na okno renderowania SFML
    bool quit;                        // Flaga okreúlajπca, czy zamknπÊ bieøπcy stan

    // --- Funkcje logiczne ---
    void CheckForQuit();              // Sprawdza warunki wyjúcia ze stanu
    bool GetQuit();                   // Zwraca status flagi quit

    // --- Metody wirtualne (do nadpisania w klasach pochodnych) ---
    virtual void EndState() = 0;                        // Czyúci dane przed usuniÍciem stanu
    virtual void Update(float dt) = 0;                  // Logika stanu (dt = delta time)
    virtual void Render(sf::RenderWindow* windowPtr) = 0; // Rysowanie grafiki dla tego stanu

private:
    // Sekcja prywatna (pusta - logika zarzπdzana przez klasy pochodne)
};