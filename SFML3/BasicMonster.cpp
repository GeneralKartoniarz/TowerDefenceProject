#include "BasicMonster.h"

// --- KONSTRUKTOR ---
// Ustawia statystyki podstawowego potwora
BasicMonster::BasicMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    mMaxHP = 100;
    mHP = mMaxHP;
    mDamage = 5;
    mGold = 10;
    mSpeed = 150.f;

    shape.setFillColor(sf::Color::Red);
}
