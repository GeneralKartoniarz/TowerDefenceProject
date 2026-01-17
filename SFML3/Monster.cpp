#include "Monster.h"
#include <cmath>
#include <iostream>

using namespace std;

/**
 * @brief Konstruktor bazowy Monster.
 * Inicjalizuje parametry fizyczne jednostki oraz jej interfejs wizualny (HUD).
 */
Monster::Monster(sf::Vector2f startPos)
{
    // --- Inicjalizacja statystyk bazowych ---
    mMaxHP = 100;
    mHP = mMaxHP;
    mDamage = 5;
    mGold = 10;
    mSpeed = 150.f;
    baseSpeed = mSpeed;
    // --- Konfiguracja reprezentacji graficznej ---
    shape.setSize({ 50.f, 50.f });
    shape.setOrigin(shape.getSize() / 2.f); // Centrowanie œrodka ciê¿koœci dla obrotów i kolizji
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);

    // --- Konfiguracja wskaŸnika zdrowia (Health Bar) ---
    // T³o paska
    hpBarBackground.setSize({ 40.f, 6.f });
    hpBarBackground.setFillColor(sf::Color(50, 50, 50));
    hpBarBackground.setOrigin({ hpBarBackground.getSize().x / 2.f, 0.f });

    // Dynamiczne wype³nienie paska
    hpBarFill.setSize({ 40.f, 6.f });
    hpBarFill.setFillColor(sf::Color::Green);
    hpBarFill.setOrigin({ hpBarFill.getSize().x / 2.f, 0.f });
}

/**
 * @brief Przetwarza logikê przemieszczania siê wzd³u¿ wêz³ów œcie¿ki.
 * Wykorzystuje normalizacjê wektora kierunku w celu uzyskania sta³ej prêdkoœci.
 */
void Monster::Update(float dt, const vector<sf::Vector2f>& path)
{
    // Weryfikacja stanu ¿ywotnoœci
    if (mHP <= 0)
        isDead = true;
    if (isStunned) {
        mSpeed = 0;
        shape.setFillColor(sf::Color(0, 200, 100));
    }
    else if(effects.empty()){
        mSpeed = baseSpeed;
        shape.setFillColor(normalColor);
    }


    // Sprawdzenie warunku zwyciêstwa potwora (dotarcie do bazy gracza)
    if (pathIndex >= (int)path.size())
    {
        reachedEnd = true;
        return;
    }

    // --- Matematyka ruchu ---
    sf::Vector2f target = path[pathIndex];
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f dir = target - pos; // Wektor ró¿nicy pozycji

    // Obliczenie dystansu przy u¿yciu twierdzenia Pitagorasa
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);

    // Detekcja osi¹gniêcia punktu orientacyjnego (Waypoint)
    if (length < 2.f)
    {
        pathIndex++; // Prze³¹czenie na kolejny punkt nawigacyjny
    }
    else
    {
        // Normalizacja wektora (dir / length) nadaje mu d³ugoœæ 1, zachowuj¹c kierunek.
        // Mno¿enie przez mSpeed i dt zapewnia ruch niezale¿ny od klatek na sekundê.
        shape.move((dir / length) * mSpeed * dt);
    }

    // Aktualizacja pozycji paska HP wzglêdem poruszaj¹cego siê potwora
    ChangeHpBar();
    UpdateEffects(dt);

}

/**
 * @brief Skaluje i pozycjonuje pasek zdrowia nad g³ow¹ potwora.
 */
void Monster::ChangeHpBar()
{
    // Obliczanie wspó³czynnika wype³nienia (0.0 do 1.0)
    float hpPercent = mHP / mMaxHP;
    if (hpPercent < 0) hpPercent = 0;

    // Aktualizacja szerokoœci zielonego wype³nienia
    hpBarFill.setSize({ 40.f * hpPercent, 6.f });

    // Synchronizacja pozycji HUD z pozycj¹ obiektu (offset pionowy -40px)
    sf::Vector2f pos = shape.getPosition();
    hpBarBackground.setPosition({ pos.x, pos.y - 40.f });
    hpBarFill.setPosition({ pos.x, pos.y - 40.f });
}

void Monster::ApplyEffect(StatusEffect type, float duration, float value)
{
    if (HasEffect(type))
        return;
    effects.push_back({ type, duration, value });
}
bool Monster::HasEffect(StatusEffect type)
{
    for (const ActiveEffect& effect : effects)
    {
        if (effect.type == type)
            return true;
    }
    return false;
}

void Monster::UpdateEffects(float dt)
{
    isStunned = false;
    mSpeed = baseSpeed;

    for (int i = effects.size() - 1; i >= 0; i--)
    {
        effects[i].duration -= dt;

        if (effects[i].duration <= 0)
        {
            effects.erase(effects.begin() + i);
            continue;
        }

        if (effects[i].type == StatusEffect::Slow)
            mSpeed = baseSpeed * effects[i].value;

        if (effects[i].type == StatusEffect::Stun)
            isStunned = true;
    }
}


/**
 * @brief Renderuje kompletny obiekt potwora (cia³o + interfejs).
 */
void Monster::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(hpBarBackground);
    window.draw(hpBarFill);
}