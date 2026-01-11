#pragma once

#include "Tower.h"
#include "Monster.h"
#include "Bullet.h"
using namespace std;
// --- PODSTAWOWA WIE¯A ---
class BasicTower : public Tower
{
public:
    // --- Konstruktor ---
    BasicTower(sf::Vector2f position);
    static constexpr int COST = 100;
    // --- Implementacje metod abstrakcyjnych ---
    void Update(float dt,vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) override;
    void Draw(sf::RenderWindow& window) override;

private:
    float attackCooldown;   // Czas pomiêdzy atakami
    float attackTimer;      // Licznik czasu
};
