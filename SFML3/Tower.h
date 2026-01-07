#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Tower
{
public:
    // --- Konstruktor ---
    // Inicjalizuje wie¿ê z okreœlonymi statystykami i tekstur¹
    Tower(int cost, float attack, float range, string name, sf::Texture texture);

    // --- Atrybuty publiczne ---
    int tCost;                 // Koszt postawienia wie¿y
    float tAttack;             // Si³a ataku/obra¿enia
    float tRange;              // Zasiêg ra¿enia
    string tName;              // Nazwa wie¿y

    // --- Grafika ---
    sf::Texture tTexture;      // Tekstura przechowywana w obiekcie
    sf::RectangleShape tShape; // Kszta³t (sprite/prostok¹t) do renderowania

private:
    // Tutaj mo¿esz dodaæ prywatne zmienne pomocnicze w przysz³oœci
};