#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>   
#include <string>

using namespace std;

/**
 * class Button
 * Uniwersalny komponent interfejsu u¿ytkownika (UI) obs³uguj¹cy interakcje myszy.
 */
class Button
{
public:
    // Inicjalizuje przycisk z przypisanym zasobem czcionki dla etykiety tekstowej
    Button(sf::Font& font);
    ~Button();

    // Elementy sk³adowe graficznej reprezentacji przycisku
    sf::RectangleShape shape;       // T³o i obramowanie przycisku
    sf::Text text;                  // Warstwa tekstowa (etykieta)
    string defText = "Test Button"; // Bufor przechowuj¹cy treœæ napisu

    // W³aœciwoœci geometryczne obiektu
    sf::Vector2f size = { 200.f, 100.f };
    sf::Vector2f position;

    // Definicje kolorów dla ró¿nych stanów interakcji
    sf::Color normalColor = sf::Color::Blue; // Barwa domyœlna
    sf::Color hoverColor = sf::Color::Red;   // Barwa po wskazaniu kursorem

    // Flaga pomocnicza do obs³ugi zdarzeñ klikniêcia
    bool wasPressed = false;

    // Aktualizuje wspó³rzêdne wszystkich sk³adowych przycisku
    void SetPosition(float x, float y);

    // Wyznacza geometryczny œrodek kszta³tu i wyrównuje do niego tekst
    void CenterText();

    // Zarz¹dza zmian¹ wygl¹du przycisku na podstawie pozycji kursora
    void UpdateHover(float x, float y);

    // Wykonuje test kolizji punktu (myszy) z obszarem prostok¹ta przycisku
    bool IsMouseOver(float mouseX, float mouseY);

    // Weryfikuje, czy w bie¿¹cej klatce nast¹pi³a interakcja potwierdzaj¹ca klikniêcie
    bool IsButtonClicked(float mouseX, float mouseY);

    // Wyœwietla t³o oraz tekst przycisku w zadanym oknie renderowania
    void Draw(sf::RenderWindow& window);
};