#include "TankMonster.h"

/**
 * @brief Konstruktor TankMonster
 * Inicjalizuje statystyki potwora o wysokiej wytrzyma³oœci i niskiej mobilnoœci.
 */
void TankMonster::LoadTexture(const string& path)
{
    if (!texture.loadFromFile(path))
    {
        cout << "B³¹d: Nie za³adowano tekstury: " << path << endl;
    }
    shape.setTexture(&texture);
}
TankMonster::TankMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    LoadTexture("assets/AI/AI3.png");
    // Statystyki wytrzyma³oœciowe (3x wy¿sze HP ni¿ BasicMonster)
    mMaxHP = 300.f;
    mHP = mMaxHP;

    // Statystyki ataku i nagrody
    mDamage = 15;        // Znaczne obra¿enia zadawane bazie gracza po dotarciu do koñca
    mGold = 25;          // Wysoka nagroda za eliminacjê ze wzglêdu na trudnoœæ pokonania

    // Kinematyka jednostki
    mSpeed = 80.f;       // Niska prêdkoœæ wymuszaj¹ca d³u¿sz¹ ekspozycjê na ogieñ wie¿
    baseSpeed = mSpeed;

    // Reprezentacja wizualna (kolor stalowy/niebieski sugeruj¹cy opancerzenie)
    normalColor = sf::Color::White;
}