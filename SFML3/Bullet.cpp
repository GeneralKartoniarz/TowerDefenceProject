#include "Bullet.h"
#include "Monster.h"
#include <cmath>
using namespace std;

Bullet::Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage, float aoeRadius,
    vector<unique_ptr<Monster>>& monsters)
    : mTarget(target), mSpeed(speed), mDamage(damage), mAoERadius(aoeRadius), mMonsters(monsters)
{
    shape.setRadius(6.f);
    shape.setOrigin({ 6.f, 6.f });
    shape.setFillColor(sf::Color(149, 0, 0));
    shape.setPosition(startPos);
}

void Bullet::Update(float dt)
{
    if (!mTarget || mTarget->isDead)
    {
        isDead = true;
        return;
    }

    sf::Vector2f targetPos = mTarget->shape.getPosition();
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = targetPos - pos;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 10.f)
    {
        if (mAoERadius > 0.f)
        {
            // AoE - wszystkie potwory w zasiêgu
            for (auto& monster : mMonsters)
            {
                float dx = monster->shape.getPosition().x - shape.getPosition().x;
                float dy = monster->shape.getPosition().y - shape.getPosition().y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist <= mAoERadius)
                    monster->mHP -= mDamage;
            }
        }
        else
        {
            mTarget->mHP -= mDamage;
        }

        isDead = true;
        return;
    }

    // poruszanie w stronê celu
    shape.move((dir / length) * mSpeed * dt);
}

void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
