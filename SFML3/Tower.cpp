#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <string>

// Konstruktor – ustawia wszystkie w³aœciwoœci wie¿y
Tower::Tower(int cost, float attack, float range, std::string name, sf::Texture texture) {
    tCost = cost;
    tAttack = attack;
    tRange = range;
    tName = name;
    tTexture = texture;
}

// Getter kosztu
int Tower::getCost() {
    return tCost;
}

// Setter kosztu
void Tower::setCost(int cost) {
    tCost = cost;
}

// Getter obra¿eñ (atak)
float Tower::getAttack() {
    return tAttack;
}

// Setter obra¿eñ (atak)
void Tower::setAttack(float attack) {
    tAttack = attack;
}

// Getter zasiêgu
float Tower::getRange() {
    return tRange;
}

// Setter zasiêgu
void Tower::setRange(float range) {
    tRange = range;
}

// Getter nazwy wie¿y
std::string Tower::getName() {
    return tName;
}

// Setter nazwy wie¿y
void Tower::setName(std::string name) {
    tName = name;
}

// Getter tekstury
sf::Texture Tower::getTexture() {
    return tTexture;
}

// Setter tekstury
void Tower::setTexture(sf::Texture texture) {
    tTexture = texture;
}
