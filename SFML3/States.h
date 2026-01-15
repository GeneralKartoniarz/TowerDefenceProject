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

/**
 * @class States
 * @brief Abstrakcyjna klasa bazowa dla wszystkich stanów aplikacji (np. Menu, Gra, Opcje).
 * * Klasa ta stanowi fundament architektury "State Pattern", wymuszaj¹c spójny interfejs
 * dla ró¿nych etapów dzia³ania programu i zarz¹dzaj¹c przep³ywem miêdzy nimi.
 */
class States
{
public:
    // --- Inicjalizacja i Cykl ¯ycia ---

    // Przypisuje wskaŸnik do g³ównego okna aplikacji, na którym operowaæ bêd¹ stany pochodne
    States(sf::RenderWindow* windowPtr);

    // Wirtualny destruktor gwarantuje bezpieczne usuwanie obiektów klas pochodnych (MainMenuState, GameState)
    virtual ~States();

    // --- Zarz¹dzanie Przep³ywem (Flow Control) ---

    // Przechowuje adres nowego stanu, który ma zast¹piæ obecny (np. po klikniêciu "Start")
    States* nextState = nullptr;

    // Referencja do kontekstu graficznego (okna), wspó³dzielona miêdzy wszystkimi stanami
    sf::RenderWindow* windowPtr;

    // Flaga sygnalizuj¹ca mened¿erowi stanów potrzebê usuniêcia bie¿¹cego obiektu
    bool quit;

    // --- Metody Pomocnicze ---

    // Weryfikuje zdarzenia systemowe pod k¹tem ¿¹dania zamkniêcia aplikacji
    void CheckForQuit();

    // Zwraca informacjê, czy bie¿¹cy stan zakoñczy³ swoje zadanie
    bool GetQuit();

    // --- Interfejs Maszyny Stanów (Polimorfizm) ---

    // Metoda wywo³ywana tu¿ przed destrukcj¹ stanu do zwolnienia unikalnych zasobów
    virtual void EndState() = 0;

    // G³ówna pêtla logiczna stanu. dt (delta time) zapewnia niezale¿noœæ od liczby klatek (FPS)
    virtual void Update(float dt) = 0;

    // G³ówna pêtla renderuj¹ca. Separacja logiki (Update) od rysowania (Render) poprawia stabilnoœæ silnika
    virtual void Render(sf::RenderWindow* windowPtr) = 0;

private:
    // Logika wewnêtrzna stanów jest hermetyzowana w klasach pochodnych
};