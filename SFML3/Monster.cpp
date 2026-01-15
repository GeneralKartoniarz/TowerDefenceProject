#include "Monster.h"
#include <cmath>
#include <iostream>

using namespace std;

/**
 * @brief Konstruktor bazowy Monster.
 * Inicjalizuje parametry fizyczne jednostki oraz jej interfejs wizualny (HUD).
 */
Monster::Monster(sf::Vector2f startPos)
{
    // --- Inicjalizacja statystyk bazowych ---
    mMaxHP = 100;
    mHP = mMaxHP;
    mDamage = 5;
    mGold = 10;
    mSpeed = 150.f;

    // --- Konfiguracja reprezentacji graficznej ---
    shape.setSize({ 50.f, 50.f });
    shape.setOrigin(shape.getSize() / 2.f); // Centrowanie œrodka ciê¿koœci dla obrotów i kolizji
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);

    // --- Konfiguracja wskaŸnika zdrowia (Health Bar) ---
    // T³o paska
    hpBarBackground.setSize({ 40.f, 6.f });
    hpBarBackground.setFillColor(sf::Color(50, 50, 50));
    hpBarBackground.setOrigin({ hpBarBackground.getSize().x / 2.f, 0.f });

    // Dynamiczne wype³nienie paska
    hpBarFill.setSize({ 40.