#include "BasicMonster.h"


void BasicMonster::LoadTexture(const string& path)
{
    if (!texture.loadFromFile(path))
    {
        cout << "B³¹d krytyczny: Nie za³adowano tekstury: " << path << endl;
    }
    shape.setTexture(&texture);
}
// Definicja konstruktora przekazuj¹cego pozycjê startow¹ do klasy bazowej
BasicMonster::BasicMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    LoadTexture("assets/AI/AI1.png");
    // Konfiguracja ¿ywotnoœci (HP)
    mMaxHP = 100.f;
    mHP = mMaxHP;

    // Definicja parametrów ekonomicznych i ofensywnych
    mDamage = 5;      // Obra¿enia zadawane po dotarciu do koñca œcie¿ki
    mGold = 10;       // Nagroda za pokonanie przeciwnika
    mSpeed = 150.f;   // Prêdkoœæ przemieszczania siê po punktach nawigacyjnych
    baseSpeed = mSpeed;

    // Personalizacja wygl¹du modelu potwora
    normalColor = (sf::Color::Red);
}