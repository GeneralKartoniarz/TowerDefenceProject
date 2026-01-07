#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Monster
{
public:
    // --- Konstruktor ---
    Monster(sf::Vector2f startPos);

    // --- Statystyki potwora ---
    int mHP;                        // Punkty ¿ycia
    int mDamage;                    // Obra¿enia zadawane bazie
    int mGold;                      // Nagroda za pokonanie
    float mSpeed;                   // Prêdkoœæ ruchu

    // --- Logika œcie¿ki i ruchu ---
    int pathIndex = 0;              // Aktualny punkt kontrolny na œcie¿ce
    bool reachedEnd = false;        // Czy potwór dotar³ do koñca mapy

    // --- Grafika ---
    sf::RectangleShape shape;       // Wizualna reprezentacja potwora

    // --- Metody g³ówne ---
    // Aktualizuje pozycjê potwora wzglêdem listy punktów (path)
    void Update(float dt, const std::vector<sf::Vector2f>& path);

    // Rysuje potwora w oknie gry
    void Draw(sf::RenderWindow& window);
};