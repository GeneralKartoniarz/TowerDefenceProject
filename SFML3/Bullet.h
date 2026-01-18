#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Monster.h"
using namespace std;

class Monster;

class Bullet
{
public:
    Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage, float aoeRadius, const vector<Monster*>& monsters, Monster::AttackType attackType);

    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    bool isDead = false;

private:
    Monster* mTarget;               // cel pocisku
    sf::Vector2f direction;
    Monster::AttackType mAttackType;
    float mSpeed;
    float mDamage;
    float mAoERadius = 0.f;         // promieñ AoE, 0 = brak AoE
    float mLifeTime = 0.2f;
    sf::CircleShape shape;

    vector<Monster*> mMonsters;     // wskaŸniki do wszystkich potworów
};
