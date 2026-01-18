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
    if (target)
    {
        sf::Vector2f dir = target->shape.getPosition() - startPos;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len != 0)
            direction = dir / len;
    }
    mSpeed = speed * 5;
}

void Bullet::Update(float dt)
{
    mLifeTime -= dt;
    if (mLifeTime <= 0.f)
    {
        isDead = true;
        return;
    }

    // ruch po linii prostej
    shape.move(direction * mSpeed * dt);

    // kolizja z potworami
    for (auto& monster : mMonsters)
    {
        if (monster->isDead)
            continue;

        float dx = monster->shape.getPosition().x - shape.getPosition().x;
        float dy = monster->shape.getPosition().y - shape.getPosition().y;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist < 12.f) // trafienie
        {
            if (mAoERadius > 0.f)
            {
                for (auto& m : mMonsters)
                {
                    float ax = m->shape.getPosition().x - shape.getPosition().x;
                    float ay = m->shape.getPosition().y - shape.getPosition().y;
                    float ad = sqrt(ax * ax + ay * ay);

                    if (ad <= mAoERadius)
                        m->mHP -= mDamage;
                }
            }
            else
            {
                monster->mHP -= mDamage;
            }

            isDead = true;
            return;
        }
    }
}


void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
