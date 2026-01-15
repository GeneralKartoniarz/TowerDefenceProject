#pragma once
#include "Monster.h"

/**
 * class BasicMonster
 * Standardowy typ przeciwnika o zbalansowanych statystykach.
 * * Dziedziczy po klasie Monster, implementuj¹c domyœlne zachowania
 * dla podstawowej jednostki wrogiej w grze.
 */
class BasicMonster : public Monster
{
public:
    /**
     * Inicjalizuje instancjê potwora w punkcie startowym œcie¿ki.
     * @param startPos Pocz¹tkowe wspó³rzêdne spawnu.
     */
    BasicMonster(sf::Vector2f startPos);
};