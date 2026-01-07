#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <string>

// --- Konstruktor ---
// Ustawia wszystkie w³aœciwoœci wie¿y na podstawie przekazanych parametrów
Tower::Tower(int cost, float attack, float range, std::string name, sf::Texture texture)
{
    this->tCost = cost;       // Przypisanie kosztu
    this->tAttack = attack;   // Przypisanie si³y ataku
    this->tRange = range;     // Przypisanie zasiêgu
    this->tName = name;       // Przypisanie nazwy wie¿y
    this->tTexture = texture; // Przypisanie tekstury
}