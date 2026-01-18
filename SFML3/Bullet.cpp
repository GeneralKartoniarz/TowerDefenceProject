#include "Bullet.h"
#include "Monster.h"
#include <cmath>
using namespace std;
class Monster;

Bullet::Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage, float aoeRadius,vector<unique_ptr<Monster>>& monsters, Monster::AttackType attackType): 
    mTarget(target), mSpeed(speed), mDamage(damage), mAoERadius(aoeRadius),mMonsters(monsters), mAttackType(attackType)
{
    // ustawienia wizualne pocisku
    shape.setRadius(6.f);
    shape.setOrigin({ 6.f, 6.f });
    shape.setFillColor(sf::Color(149, 0, 0));
    shape.setPosition(startPos);

    // kierunek ruchu (po linii prostej w stronê pocz¹tkowej pozycji celu)
    if (target)
    {
        sf::Vector2f dir = target->shape.getPosition() - startPos;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len != 0.f)
            direction = dir / len;
    }

    // opcjonalnie mo¿na przyspieszyæ pocisk, jeœli chcesz
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

    shape.move(direction * mSpeed * dt);

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
                        m->TakeDamage(mDamage, mAttackType);
                }
            }
            else
            {
                monster->TakeDamage(mDamage, mAttackType);
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
