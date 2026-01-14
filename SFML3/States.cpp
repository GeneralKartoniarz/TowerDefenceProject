#include "States.h"

// --- Konstruktor ---
// Inicjalizuje stan gry, przypisuj¹c wskaŸnik na okno i ustawiaj¹c flagê wyjœcia na false
States::States(sf::RenderWindow* windowPtr)
{
    this->windowPtr = windowPtr;
    this->quit = false;
}

// --- Destruktor ---
// Wirtualny destruktor klasy bazowej
States::~States()
{
}