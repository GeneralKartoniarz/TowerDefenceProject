#include "EMPtower.h"
#include "Tower.h"
#include "Monster.h"
EMPtower::EMPtower(sf::Vector2f position)
{
    LoadTexture("assets/emp_tower/emp1.png");

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
void EMPtower::Update(float dt,vector<unique_ptr<Monster>>& monsters,vector<unique_ptr<Bullet>>& bullets)
{
    attackTimer += dt;
    if (attackTimer < attackCooldown)
        return;
    Monster* target = nullptr;
    float closestDistance = tRange;
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
    if (target)
    {
        RotateToEnemy(target);
        target->ApplyEffect(Monster::StatusEffect::Slow, 2.f, 0.5f);
        attackTimer = 0.f; // Resetowanie licznika prze³adowania
    }

}

void EMPtower::Draw(sf::RenderWindow& window)
{
    window.draw(tShape);

}
