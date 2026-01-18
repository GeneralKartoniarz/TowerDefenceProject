#include "HackerTower.h"
#include "Tower.h"
#include "Monster.h"
#include <string>
HackerTower::HackerTower(sf::Vector2f position):shootSound(shootBuffer)
{

    LoadTexture("assets/hacker_tower/"+path+to_string(level)+".png");

    // Konfiguracja parametrów bojowych i ekonomicznych
    tCost = COST;
    tAttack = 25.f;
    tRange = 200.f;
    tName = "Hacker Tower";

    // Ustawienie mechaniki szybkostrzelnoœci
    attackCooldown = 3.f;
    attackTimer = 0.f;

    if (!shootBuffer.loadFromFile("assets/sfx/hackerSound.wav"))
        cout << "c";
    shootSound.setVolume(40.f);

    // Definiowanie w³aœciwoœci transformacji obiektu
    tShape.setSize({ 50.f, 50.f });
    tShape.setOrigin(tShape.getSize() / 2.f); // Centrowanie punktu obrotu/pozycji
    tShape.setPosition(position);
}

void HackerTower::Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets)
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
            if(!monster.get()->HasEffect(Monster::StatusEffect::Stun))
                target = monster.get();
        }
    }
    if (target && target->mMaxHP<1000)//zalosne wiem
    {
        RotateToEnemy(target);
        target->ApplyEffect(Monster::StatusEffect::Stun, 2.f, .6f);
        target->mHP -= 50;
        attackTimer = 0.f; // Resetowanie licznika prze³adowania
        shootSound.play();
    }
    LoadTexture("assets/hacker_tower/" + path + to_string(level) + ".png");

}

void HackerTower::Draw(sf::RenderWindow& window)
{
    window.draw(tShape);
    if (isRangeShown) {
        sf::CircleShape rangeCircle(this->tRange);
        rangeCircle.setOrigin({ this->tRange, this->tRange });
        rangeCircle.setPosition(this->tShape.getPosition());
        rangeCircle.setFillColor(sf::Color(250, 50, 50, 100));
        window.draw(rangeCircle);
    }
}
