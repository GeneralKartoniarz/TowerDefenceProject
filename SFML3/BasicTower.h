#pragma once

#include "Tower.h"
#include "Monster.h"
#include "Bullet.h"
#include <SFML/Audio.hpp>

using namespace std;

/**
 * class BasicTower
 * Podstawowa jednostka obronna dziedzicz¹ca po klasie bazowej Tower.
 * Wykrywa przeciwników w zasiêgu i wystrzeliwuje standardowe pociski.
 */
class BasicTower : public Tower
{
public:
    // Inicjalizuje wie¿ê na okreœlonych wspó³rzêdnych mapy
    BasicTower(sf::Vector2f position);

    // Sta³y koszt zakupu jednostki wykorzystywany przez system ekonomii gry
    static constexpr int COST = 100;

    /**
     * G³ówna pêtla logiczna wie¿y:
     * - Odlicza czas do kolejnego strza³u
     * - Wyszukuje najbli¿szy cel z listy potworów
     * - Generuje nowe obiekty typu Bullet
     */
    void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) override;

    // Odpowiada za wyœwietlenie grafiki wie¿y oraz opcjonalnych elema entów (np. zasiêgu)
    void Draw(sf::RenderWindow& window) override;

private:
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
};