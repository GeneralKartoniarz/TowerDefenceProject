#pragma once

#include "Tower.h"
#include "Monster.h"
#include <iostream>
using namespace std;
class BasicTower : public Tower
{
public:
    BasicTower(sf::Vector2f position);

    void Update(float dt, vector<unique_ptr<Monster>>& monsters);
    void Draw(sf::RenderWindow& window);

private:
    float attackCooldown;   // Czas pomiêdzy atakami
    float attackTimer;      // Licznik czasu
};