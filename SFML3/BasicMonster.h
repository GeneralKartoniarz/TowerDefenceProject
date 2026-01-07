#pragma once
#include "Monster.h"

// --- PODSTAWOWY POTWÓR ---
// Wolniejszy, œrednie HP – klasyczny przeciwnik
class BasicMonster : public Monster
{
public:
    BasicMonster(sf::Vector2f startPos);
};
