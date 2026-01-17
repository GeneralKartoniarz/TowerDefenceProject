#pragma once

#include "Tower.h"
#include "Monster.h"
#include "Bullet.h"

using namespace std;

/**
 * @class LaserTower
 * @brief Specjalistyczna jednostka obronna o wysokich obra¿eniach.
 * * Wie¿a typu Laser charakteryzuje siê wiêkszym zasiêgiem i si³¹ ataku,
 * co czyni j¹ idealn¹ kontr¹ na przeciwników typu Boss/Tank.
 * Wykorzystuje mechanizm cooldownu do kontrolowania czêstotliwoœci strza³ów.
 */
class LaserTower : public Tower
{
public:
    /**
     * @brief Inicjalizuje wie¿ê laserow¹ na wybranym kafelku.
     * @param position Wspó³rzêdne œrodka kafelka (sf::Vector2f).
     */
    LaserTower(sf::Vector2f position);

    // Statyczny koszt zakupu, dostêpny dla logiki sklepu w GameState bez instancji klasy
    static constexpr int COST = 300;

    /**
     * @brief Przeszukuje listê potworów w zasiêgu i generuje pociski.
     * @param dt Czas delty (Delta Time).
     * @param monsters Referencja do kontenera aktywnych wrogów.
     * @param bullets Referencja do kontenera pocisków, gdzie dodawane s¹ nowe obiekty Bullet.
     */
    void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) override;

    /**
     * @brief Renderuje teksturê wie¿y.
     */
    void Draw(sf::RenderWindow& window) override;

private:
};