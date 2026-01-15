#include "States.h"

/**
 * @brief Konstruktor klasy bazowej States.
 * Inicjalizuje wspólny kontekst dla wszystkich stanów gry.
 * * @param windowPtr WskaŸnik do aktywnego okna renderowania (sf::RenderWindow).
 * Dziêki przekazaniu wskaŸnika, ka¿dy stan (menu, gra, opcje) ma dostêp do tego samego okna.
 */
States::States(sf::RenderWindow* windowPtr)
{
    this->windowPtr = windowPtr;

    // Flaga steruj¹ca cyklem ¿ycia stanu. 
    // Ustawienie na 'true' informuje mened¿era stanów o koniecznoœci usuniêcia tego obiektu.
    this->quit = false;
}

/**
 * @brief Wirtualny destruktor klasy bazowej.
 * Jest on kluczowy w hierarchii dziedziczenia. Pozwala na bezpieczne wywo³anie
 * destruktorów klas pochodnych (np. GameState, MainMenuState) podczas usuwania
 * obiektu poprzez wskaŸnik typu States*.
 */
States::~States()
{
}

/**
 * @brief Metoda sprawdzaj¹ca sygna³y zakoñczenia stanu.
 */
void States::CheckForQuit()
{
    if (this->quit)
    {
        // Logika przygotowania do zamkniêcia stanu
        this->EndState();
    }
}

/**
 * @brief Getter statusu zakoñczenia.
 * @return Zwraca true, jeœli stan powinien zostaæ usuniêty z pamiêci.
 */
bool States::GetQuit()
{
    return this->quit;
}