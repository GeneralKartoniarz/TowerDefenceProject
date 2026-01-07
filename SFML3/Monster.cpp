#include "Monster.h"
#include <cmath>
#include <vector>
Monster::Monster(sf::Vector2f startPos)
{
    mHP = 100;
    mDamage = 5;
    mGold = 10;
    mSpeed = 500.f;

    shape.setSize({ 50.f, 50.f });
    shape.setOrigin(shape.getSize() / 2.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);
}

void Monster::Update(float dt, const std::vector<sf::Vector2f>& path)
{
    if (pathIndex >= path.size())
    {
        reachedEnd = true;
        return;
    }

    sf::Vector2f target = path[pathIndex];
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = target - pos;

    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (length < 2.f)
    {
        pathIndex++;
    }
    else
    {
        shape.move((dir / length) * mSpeed * dt);
    }
}

void Monster::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}
