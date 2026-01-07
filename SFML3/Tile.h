#pragma once

#include <iostream>   
#include <string>    
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Tile
{
public:
    // --- Typy wyliczeniowe ---
    enum class TileState
    {
        Path,      // Œcie¿ka, po której id¹ przeciwnicy
        Placement, // Miejsce, gdzie mo¿na postawiæ wie¿ê
        Locked     // Pole zablokowane/zajête
    };

    // --- Konstruktor i destruktor ---
    Tile(sf::Vector2f position, float size, TileState state);
    ~Tile();

    // --- W³aœciwoœci publiczne ---
    TileState state;                // Aktualny stan kafelka
    sf::RectangleShape shape;       // Obiekt graficzny SFML
    float size = 50.f;              // Rozmiar boku kafelka
    sf::Color normalColor = sf::Color(45, 191, 0); // Domyœlny kolor (zielony)

    // --- Metody obs³ugi ---
    void SetPosition(float x, float y);             // Ustawia now¹ pozycjê kafelka
    bool IsMouseOver(float mouseX, float mouseY);   // Sprawdza, czy mysz znajduje siê nad kafelkiem
    bool IsButtonClicked(float mouseX, float mouseY); // Sprawdza klikniêcie w kafelek

    // --- Renderowanie i aktualizacja ---
    void Draw(sf::RenderWindow& window);            // Rysuje kafelek w oknie
    void Refresh();                                 // Odœwie¿a stan/wygl¹d kafelka

private:
    // Sekcja prywatna (obecnie pusta)
};