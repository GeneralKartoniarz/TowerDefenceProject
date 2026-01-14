#include "Monster.h"
#include <cmath>
#include <iostream>
using namespace std;
// --- KONSTRUKTOR BAZOWY ---
// Inicjalizuje wspólne elementy graficzne potwora
Monster::Monster(sf::Vector2f startPos)
{
    // --- Statystyki ---
    mMaxHP = 100;
    mHP = mMaxHP;
    mDamage = 5;
    mGold = 10;
    mSpeed = 150.f;

    // --- Wygl¹d potwora ---
    shape.setSize({ 50.f, 50.f });
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);

    // --- T³o paska HP ---
    hpBarBackground.setSize({ 40.f, 6.f });
    hpBarBackground.setFillColor(sf::Color(50, 50, 50));
    hpBarBackground.setOrigin({ hpBarBackground.getSize().x / 2.f, 0.f });

    // --- Wype³nienie paska HP ---
    hpBarFill.setSize({ 40.f, 6.f });
    hpBarFill.setFillColor(sf::Color::Green);
    hpBarFill.setOrigin({hpBarFill.getSize().x / 2.f, 0.f});
}

// --- AKTUALIZACJA LOGIKI ---
// Odpowiada za poruszanie siê potwora po œcie¿ce
void Monster::Update(float dt, const vector<sf::Vector2f>& path)
{
    if (mHP <= 0)
        isDead = true;
    // Sprawdzenie czy potwór dotar³ do koñca œcie¿ki
    if (pathIndex >= path.size())
    {
        reachedEnd = true;
        return;
    }

    // Wyznaczenie celu i kierunku ruchu
    sf::Vector2f target = path[pathIndex];
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = target - pos;

    // Obliczenie d³ugoœci wektora (odleg³oœci do celu)
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    // Jeœli potwór jest bardzo blisko punktu – przechodzi do nastêpnego
    if (length < 2.f)
    {
        pathIndex++;
    }
    else
    {
        // Ruch potwora z uwzglêdnieniem czasu klatki (dt)
        shape.move((dir / length) * mSpeed * dt);
    }
    ChangeHpBar();
}
void Monster::ChangeHpBar()
{
    float hpPercent = mHP / mMaxHP;

    hpBarFill.setSize({ 40.f * hpPercent, 6.f });

    sf::Vector2f pos = shape.getPosition();
    hpBarBackground.setPosition({ pos.x, pos.y - 40.f });
    hpBarFill.setPosition({pos.x - (40.f - hpBarBackground.getSize().x) / 2.f, pos.y - 40.f});
}

// --- RENDEROWANIE ---
// Rysuje potwora na ekranie
void Monster::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(hpBarBackground);
    window.draw(hpBarFill);
}
