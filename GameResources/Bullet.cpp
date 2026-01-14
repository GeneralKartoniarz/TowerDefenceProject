#include "Bullet.h"
#include "Monster.h"
#include <cmath>
using namespace std;
// --- Konstruktor ---
Bullet::Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage)
{
    mTarget = target;
    mSpeed = speed;
    mDamage = damage;

    shape.setRadius(6.f);
    shape.setOrigin({ 6.f, 6.f });
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(startPos);
}

// --- Aktualizacja ---
// Pocisk leci w stronê potwora
void Bullet::Update(float dt)
{
    // Jeœli cel znikn¹³
    if (!mTarget || mTarget->isDead)
    {
        isDead = true;
        return;
    }

    sf::Vector2f targetPos = mTarget->shape.getPosition();
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = targetPos - pos;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    // Trafienie
    if (length < 10.f)
    {
        mTarget->mHP -= mDamage;
        isDead = true;
        return;
    }

    shape.move((dir / length) * mSpeed * dt);
}

// --- Render ---
void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
