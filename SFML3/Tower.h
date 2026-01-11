#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Bullet.h"
using namespace std;
class Monster;

// --- KLASA ABSTRAKCYJNA WIE¯Y ---
class Tower
{
public:
    virtual ~Tower() = default;

    // --- Metody abstrakcyjne ---
    // Ka¿da wie¿a MUSI je zaimplementowaæ
    virtual void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) = 0;

    virtual void Draw(sf::RenderWindow& window) = 0;

protected:
    // --- Statystyki wie¿y ---
    int tCost;
    float tAttack;
    float tRange;
    std::string tName;

    // --- Grafika ---
    sf::RectangleShape tShape;
};
