#include "Monster.h"
#include <cmath>
#include <vector>
using namespace std;
// --- Konstruktor ---
// Ustawia bazowe statystyki potwora oraz inicjalizuje jego wygl¹d i pozycjê startow¹
Monster::Monster(sf::Vector2f startPos)
{
    mHP = 100;
    mDamage = 5;
    mGold = 10;
    mSpeed = 1500.f;

    shape.setSize({ 50.f, 50.f });
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);
}

// --- Logika Aktualizacji ---
// Obs³uguje ruch potwora po œcie¿ce oraz sprawdzanie punktów kontrolnych (waypoints)
void Monster::Update(float dt, const vector<sf::Vector2f>& path)
{
    // Sprawdzenie, czy potwór przeszed³ ju¿ ca³¹ œcie¿kê
    if (pathIndex >= path.size())
    {
        reachedEnd = true;
        return;
    }

    sf::Vector2f target = path[pathIndex];
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = target - pos;

    // Obliczanie odleg³oœci do celu (twierdzenie Pitagorasa)
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    // Jeœli potwór jest wystarczaj¹co blisko punktu, prze³¹cza siê na kolejny cel
    if (length < 2.f)
    {
        pathIndex++;
    }
    else
    {
        // Ruch w stronê celu z uwzglêdnieniem czasu klatki (dt)
        shape.move((dir / length) * mSpeed * dt);
    }
}

// --- Renderowanie ---
// Rysuje potwora w oknie gry
void Monster::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}