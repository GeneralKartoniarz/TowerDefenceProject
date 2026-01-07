#include "FastMonster.h"

// --- KONSTRUKTOR ---
// Ustawia statystyki szybkiego potwora
FastMonster::FastMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    mMaxHP = 60;
    mHP = mMaxHP;
    mDamage = 3;
    mGold = 8;
    mSpeed = 250.f;

    shape.setFillColor(sf::Color::Yellow);
}
