#pragma once
#include "Monster.h"

// --- SZYBKI POTWÓR ---
// Ma³o HP, ale wysoka prêdkoœæ
class FastMonster : public Monster
{
public:
    FastMonster(sf::Vector2f startPos);
};
