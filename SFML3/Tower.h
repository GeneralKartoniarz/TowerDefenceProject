#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Tower
{
public:
    // --- Wirtualny destruktor ---
    // WYMAGANY w klasach bazowych u¿ywanych polimorficznie
    virtual ~Tower();

    // --- Atrybuty wspólne dla wszystkich wie¿ ---
    int tCost;                 // Koszt postawienia wie¿y
    float tAttack;             // Si³a ataku
    float tRange;              // Zasiêg ataku
    string tName;              // Nazwa wie¿y

    // --- Grafika ---
    sf::RectangleShape tShape; // Kszta³t wie¿y do renderowania

    // --- Metody czysto wirtualne ---
    // Ka¿da wie¿a MUSI je zaimplementowaæ
    virtual void Update(float dt) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
};