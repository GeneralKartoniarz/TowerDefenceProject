#include "Bullet.h"
#include "Monster.h"
#include <cmath>

using namespace std;

Bullet::Bullet(sf::Vector2f startPos, Monster* target, float speed, float damage)
{
    // Inicjalizacja parametrów mechanicznych
    mTarget = target;
    mSpeed = speed;
    mDamage = damage;

    // Konfiguracja wygl¹du i punktu zakotwiczenia pocisku
    shape.setRadius(6.f);
    shape.setOrigin({ 6.f, 6.f }); // Œrodek ko³a jako punkt odniesienia
    shape.setFillColor(sf::Color(149, 0, 0));
    shape.setPosition(startPos);
}

void Bullet::Update(float dt)
{
    // Weryfikacja czy cel nadal istnieje i jest aktywny
    if (!mTarget || mTarget->isDead)
    {
        isDead = true;
        return;
    }

    // Obliczanie wektora kierunkowego do celu
    sf::Vector2f targetPos = mTarget->shape.getPosition();
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = targetPos - pos;

    // Wyznaczanie dystansu przy u¿yciu twierdzenia Pitagorasa
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    // Sprawdzanie kolizji (trafienie nastêpuje przy zbli¿eniu siê na ma³¹ odleg³oœæ)
    if (length < 10.f)
    {
        mTarget->mHP -= mDamage; // Zadanie obra¿eñ przeciwnikowi
        isDead = true;           // Dezaktywacja pocisku po trafieniu
        return;
    }

    // Normalizacja wektora i przemieszczenie pocisku w stronê celu
    shape.move((dir / length) * mSpeed * dt);
}

void Bullet::Draw(sf::RenderWindow& window)
{
    // Wyœwietlanie obiektu w oknie aplikacji
    window.draw(shape);
}