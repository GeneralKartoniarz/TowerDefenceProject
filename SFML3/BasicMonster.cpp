#include "BasicMonster.h"

// Definicja konstruktora przekazuj¹cego pozycjê startow¹ do klasy bazowej
BasicMonster::BasicMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    // Konfiguracja ¿ywotnoœci (HP)
    mMaxHP = 100.f;
    mHP = mMaxHP;

    // Definicja parametrów ekonomicznych i ofensywnych
    mDamage = 5;      // Obra¿enia zadawane po dotarciu do koñca œcie¿ki
    mGold = 10;       // Nagroda za pokonanie przeciwnika
    mSpeed = 150.f;   // Prêdkoœæ przemieszczania siê po punktach nawigacyjnych

    // Personalizacja wygl¹du modelu potwora
    shape.setFillColor(sf::Color::Red);
}