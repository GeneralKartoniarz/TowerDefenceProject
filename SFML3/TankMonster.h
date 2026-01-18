#pragma once
#include "Monster.h"

/**
 * @class TankMonster
 * @brief Typ przeciwnika o wysokiej wytrzyma³oœci, pe³ni¹cy rolê "tankera".
 * * Klasa ta definiuje jednostkê, która ze wzglêdu na du¿¹ pulê punktów ¿ycia
 * ma za zadanie absorbowaæ ogieñ wie¿, os³aniaj¹c szybsze i s³absze potwory.
 */
class TankMonster : public Monster
{
public:
    /**
     * @brief Inicjalizuje potwora typu Tank na okreœlonej pozycji.
     * @param startPos Pocz¹tkowe wspó³rzêdne spawnu na œcie¿ce.
     */
    TankMonster(sf::Vector2f startPos);
    sf::Texture texture;       
    void LoadTexture(const string& path);
};