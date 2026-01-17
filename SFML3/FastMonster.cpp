#include "FastMonster.h"

// Inicjalizacja instancji szybkiego przeciwnika poprzez konstruktor klasy bazowej
FastMonster::FastMonster(sf::Vector2f startPos)
    : Monster(startPos)
{
    // Konfiguracja wytrzyma³oœci - ni¿sza wartoœæ HP czyni go podatnym na pojedyncze ataki
    mMaxHP = 60.f;
    mHP = mMaxHP;

    // Statystyki ekonomiczne i wp³yw na ¿ycie gracza
    mDamage = 3;      // Mniejsze obra¿enia bazowe dla zachowania balansu
    mGold = 8;        // Nagroda za eliminacjê jednostki
    mSpeed = 250.f;   // Znacznie zwiêkszona prêdkoœæ ruchu wzglêdem standardowych jednostek
    baseSpeed = mSpeed;
    // Wyró¿nienie wizualne jednostki na mapie gry
    shape.setFillColor(sf::Color::Yellow);
}