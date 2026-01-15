#pragma once
#include "Monster.h"

/**
 * class FastMonster
 * Wyspecjalizowany typ przeciwnika stawiaj¹cy na mobilnoœæ kosztem wytrzyma³oœci.
 * * Klasa implementuje wariant potwora, którego g³ównym atutem jest szybkoœæ,
 * co wymusza na graczu budowê wie¿ o wysokiej czêstotliwoœci strza³u.
 */
class FastMonster : public Monster
{
public:
    /**
     * Inicjalizuje szybkiego potwora na zadanej pozycji startowej.
     * @param startPos Wspó³rzêdne punktu pocz¹tkowego na œcie¿ce.
     */
    FastMonster(sf::Vector2f startPos);
};