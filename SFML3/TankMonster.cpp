#include "TankMonster.h"

// --- KONSTRUKTOR ---
// Ustawia statystyki ciê¿kiego potwora
TankMonster::TankMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    mMaxHP = 300.f;
    mHP = mMaxHP;
    mDamage = 15;
    mGold = 25;
    mSpeed = 80.f;

    shape.setFillColor(sf::Color(100, 100, 255));
}


