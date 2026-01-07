#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Monster
{
public:
    sf::RectangleShape shape;

    int mHP;
    int mDamage;
    int mGold;
    float mSpeed;

    int pathIndex = 0;
    bool reachedEnd = false;

    Monster(sf::Vector2f startPos);

    void Update(float dt, const std::vector<sf::Vector2f>& path);
    void Draw(sf::RenderWindow& window);
};
