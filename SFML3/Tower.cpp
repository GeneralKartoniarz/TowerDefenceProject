#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <string>

// Konstruktor – ustawia wszystkie w³aœciwoœci wie¿y
Tower::Tower(int cost, float attack, float range, std::string name, sf::Texture texture) {
    this->tCost = cost;
    this->tAttack = attack;
    this->tRange = range;
    this->tName = name;
    this->tTexture = texture;
}
