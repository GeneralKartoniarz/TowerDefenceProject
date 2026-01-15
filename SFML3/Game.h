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

/**
 * class Game
 * G³ówna klasa silnika zarz¹dzaj¹ca cyklem ¿ycia aplikacji, oknem oraz maszyna stanów.
 */
class Game
{
public:
    // Zarz¹dzaj¹ alokacj¹ i zwalnianiem zasobów systemowych silnika
    Game();
    ~Game();

    // Inicjuje g³ówny cykl przetwarzania aplikacji
    void Run();

    // Przekazuje czas delty do aktualnie aktywnego stanu logicznego
    void Update(float dt);

    // Koordynuje proces czyszczenia bufora i renderowania grafiki
    void Render();

    // Konfiguruje parametry techniczne okna (rozdzielczoœæ, VSync, tytu³)
    void InitWindow();

    // Przygotowuje pocz¹tkowe obiekty stanów (np. Menu, Gra w³aœciwa)
    void InitStates();

    // Przechwytuje i dystrybuuje sygna³y z urz¹dzeñ wejœcia oraz systemu operacyjnego
    void UpdateEvent();

private:
    // Zarz¹dzanie zasobami okna i synchronizacj¹ czasu
    sf::RenderWindow* windowPtr; // dynamicznie alokowane okno renderowania
    sf::Clock dtClock;           // Precyzyjny licznik czasu rzeczywistego
    float dt;                    // Zmienna przechowuj¹ca czas trwania ostatniej klatki

    // Mechanizm maszyny stanów (State Machine)
    vector<States*> states;      // Stos/lista dostêpnych modu³ów funkcjonalnych gry
    int activeState;             // WskaŸnik na bie¿¹cy kontekst wykonawczy

    // Kontener na dane zdarzeñ systemowych
    optional<sf::Event> ev;
};