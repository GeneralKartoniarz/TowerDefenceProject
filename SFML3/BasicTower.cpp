#include "BasicTower.h"
#include <cmath>
using namespace std;
// --- Konstruktor ---
// Inicjalizuje podstawow¹ wie¿ê z domyœlnymi statystykami
BasicTower::BasicTower(sf::Vector2f position)
{
    // --- Statystyki ---
    tCost = 100;
    tAttack = 25.f;
    tRange = 200.f;
    tName = "Basic Tower";

    attackCooldown = 0.8f;
    attackTimer = 0.f;

    // --- Grafika ---
    tShape.setSize({ 50.f, 50.f });
    tShape.setOrigin(tShape.getSize() / 2.f);
    tShape.setFillColor(sf::Color::Blue);
    tShape.setPosition(position);
}

// --- Aktualizacja wie¿y ---
// Odpowiada za cooldown oraz atakowanie potworów
void BasicTower::Update(float dt,vector<unique_ptr<Monster>>& monsters)
{
    attackTimer += dt;

    // Jeœli wie¿a nie jest gotowa do strza³u
    if (attackTimer < attackCooldown)
        return;

    Monster* target = nullptr;
    float closestDistance = tRange;

    // Szukanie najbli¿szego potwora w zasiêgu
    for (auto& monster : monsters)
    {
        sf::Vector2f mPos = monster->shape.getPosition();
        sf::Vector2f tPos = tShape.getPosition();

        float dx = mPos.x - tPos.x;
        float dy = mPos.y - tPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= closestDistance)
        {
            closestDistance = distance;
            target = monster.get();
        }
    }

    // Jeœli znaleziono cel – atak
    if (target)
    {
        target->mHP -= static_cast<int>(tAttack);
        attackTimer = 0.f;
    }
}

// --- Renderowanie ---
// Rysuje wie¿ê na planszy
void BasicTower::Draw(sf::RenderWindow& window)
{
    window.draw(tShape);
}
