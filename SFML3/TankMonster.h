#pragma once
#include "Monster.h"

// --- TANK / BOSS ---
// Wolny, bardzo du¿o HP, wysokie obra¿enia
class TankMonster : public Monster
{
public:
    TankMonster(sf::Vector2f startPos);
};
