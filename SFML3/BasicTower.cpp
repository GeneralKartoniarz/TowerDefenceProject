#include "BasicTower.h"
#include "Bullet.h"
#include <cmath>

using namespace std;

BasicTower::BasicTower(sf::Vector2f position)
{
    // £adowanie zasobów graficznych
    LoadTexture("assets/cassual_tower/cas1.png");

    // Konfiguracja parametrów bojowych i ekonomicznych
    tCost = COST;
    tAttack = 25.f;
    tRange = 200.f;
    tName = "Basic Tower";

    // Ustawienie mechaniki szybkostrzelnoœci
    attackCooldown = 0.4f;
    attackTimer = 0.f;

    // Definiowanie w³aœciwoœci transformacji obiektu
    tShape.setSize({ 50.f, 50.f });
    tShape.setOrigin(tShape.getSize() / 2.f); // Centrowanie punktu obrotu/pozycji
    tShape.setPosition(position);
}

void BasicTower::Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets)
{
    // Akumulacja czasu od ostatniego strza³u
    attackTimer += dt;
    if (attackTimer < attackCooldown)
        return;

    Monster* target = nullptr;
    float closestDistance = tRange;

    // Algorytm wyszukiwania najbli¿szego przeciwnika w zasiêgu (Nearest Neighbor)
    for (auto& monster : monsters)
    {
        sf::Vector2f mPos = monster->shape.getPosition();
        sf::Vector2f tPos = tShape.getPosition();

        // Obliczanie odleg³oœci euklidesowej
        float dx = mPos.x - tPos.x;
        float dy = mPos.y - tPos.y;
        float dist = sqrt(dx * dx + dy * dy);

        // Wybór celu znajduj¹cego siê najbli¿ej wie¿y
        if (dist <= closestDistance)
        {
            closestDistance = dist;
            target = monster.get();
        }
    }

    // Procedura generowania pocisku po znalezieniu prawid³owego celu
    if (target)
    {
        RotateToEnemy(target);
        bullets.push_back(make_unique<Bullet>(tShape.getPosition(), target, 600.f, (tAttack), 0.f, monsters));
        attackTimer = 0.f; // Resetowanie licznika prze³adowania
    }
}

void BasicTower::Draw(sf::RenderWindow& window)
{
    // Przekazanie obiektu graficznego do bufora renderowania
    window.draw(tShape);
}