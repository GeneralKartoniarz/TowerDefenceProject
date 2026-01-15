#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Monster;

/**
 * class Bullet
 * Reprezentuje pocisk wystrzeliwany przez wie¿ê w stronê konkretnego potwora.
 */
class Bullet
{
public:
    // Inicjalizuje pocisk z okreœlon¹ pozycj¹ startow¹, celem oraz statystykami
    Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage);

    // Aktualizuje trajektoriê lotu pocisku w stronê celu
    void Update(float dt);

    // Renderuje wizualn¹ reprezentacjê pocisku w oknie gry
    void Draw(sf::RenderWindow& window);

    // Flaga okreœlaj¹ca, czy pocisk trafi³ w cel lub powinien zostaæ usuniêty z pamiêci
    bool isDead = false;

private:
    Monster* mTarget;            // WskaŸnik na przeciwnika, w którego celuje pocisk
    float mSpeed;                // Sta³a prêdkoœæ przemieszczania siê obiektu
    float mDamage;               // Wartoœæ punktów ¿ycia odbierana celowi przy kolizji

    sf::CircleShape shape;       // Komponent graficzny (kszta³t) pocisku
};