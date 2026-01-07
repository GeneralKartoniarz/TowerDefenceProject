#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>   
#include <string>

using namespace std;

class Button
{
public:
    // --- Konstruktor i Destruktor ---
    Button(sf::Font& font);
    ~Button();

    // --- Sk³adniki wizualne ---
    sf::RectangleShape shape;       // Kszta³t przycisku
    sf::Text text;                  // Tekst wyœwietlany na przycisku
    string defText = "Test Button"; // Domyœlna treœæ napisu

    // --- Transformacje i wymiary ---
    sf::Vector2f size = { 200.f, 100.f };
    sf::Vector2f position;

    // --- Stylistyka ---
    sf::Color normalColor = sf::Color::Blue; // Kolor w spoczynku
    sf::Color hoverColor = sf::Color::Red;   // Kolor po najechaniu mysz¹

    // --- Metody modyfikuj¹ce ---
    void SetPosition(float x, float y);      // Ustawia pozycjê przycisku i tekstu
    void CenterText();                       // Wyœrodkowuje tekst wewn¹trz ramki

    // --- Logika i interakcja ---
    void UpdateHover(float x, float y);      // Zmienia kolor, jeœli mysz jest nad przyciskiem
    bool IsMouseOver(float mouseX, float mouseY);    // Sprawdza kolizjê z myszk¹
    bool IsButtonClicked(float mouseX, float mouseY); // Sprawdza fakt klikniêcia

    // --- Renderowanie ---
    void Draw(sf::RenderWindow& window);     // Rysuje kompletny przycisk w oknie
};