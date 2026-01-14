#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Monster;

// --- KLASA POCISKU ---
class Bullet
{
public:
    // --- Konstruktor ---
    Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage);

    // --- Logika ---
    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    // --- Stan ---
    bool isDead = false;

private:
    Monster* mTarget;            // Cel pocisku
    float mSpeed;                // Prêdkoœæ lotu
    float mDamage;                 // Obra¿enia

    sf::CircleShape shape;       // Grafika pocisku
};
