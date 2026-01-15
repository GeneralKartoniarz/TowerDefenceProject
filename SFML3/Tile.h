#pragma once

#include <iostream>   
#include <string>    
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/**
 * @class Tile
 * @brief Podstawowa jednostka siatki mapy (Grid), zarz¹dzaj¹ca logik¹ pod³o¿a i interakcj¹.
 */
class Tile
{
public:
    /**
     * @enum TileState
     * @brief Definiuje przeznaczenie kafelka w mechanice gry.
     */
    enum class TileState
    {
        Path,      // Teren przeznaczony wy³¹cznie dla ruchu jednostek Monster
        Placement, // Wolne pole umo¿liwiaj¹ce postawienie nowej wie¿y (Tower)
        Locked     // Pole zajête przez wie¿ê lub przeszkodê terenow¹
    };

    // Inicjalizuje kafelek o zadanych parametrach geometrycznych i logicznych
    Tile(sf::Vector2f position, float size, TileState state);
    ~Tile();

    // --- W³aœciwoœci publiczne i stan ---
    TileState state;                // Bie¿¹ca rola kafelka w systemie gry
    sf::RectangleShape shape;       // Reprezentacja graficzna w silniku SFML
    float size = 50.f;              // Skala kafelka (szerokoœæ i wysokoœæ)
    sf::Color normalColor = sf::Color(255, 255, 255, 255); // Bazowa barwa kafelka

    // Obs³uga zdarzeñ wejœcia (Input handling)
    bool wasPressed = false;        // Flaga zapobiegaj¹ca wielokrotnemu klikniêciu (debouncing)

    // --- Zarz¹dzanie zasobami graficznymi ---
    sf::Texture texture;            // Unikalna tekstura pod³o¿a
    void LoadTexture(const string& path);
    static vector<string> placementPaths; // Lista dostêpnych wariantów tekstur dla pól budowy

    // --- Metody transformacji i interakcji ---
    void SetPosition(float x, float y);
    bool IsMouseOver(float mouseX, float mouseY);   // Test kolizji punktu myszy z obszarem AABB
    bool IsButtonClicked(float mouseX, float mouseY); // Weryfikacja interakcji lewym przyciskiem

    // --- Cykl ¿ycia obiektu graficznego ---
    void Draw(sf::RenderWindow& window);

    /**
     * @brief Synchronizuje kolor i teksturê kafelka z jego aktualnym stanem logicznym.
     * Wywo³ywana m.in. po postawieniu wie¿y w celu zmiany stanu na Locked.
     */
    void Refresh();

private:
    // Prywatne dane pomocnicze
};