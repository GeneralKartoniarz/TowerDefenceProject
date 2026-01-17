#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Monster
 * @brief Abstrakcyjna klasa bazowa definiuj¹ca zachowanie i atrybuty przeciwników.
 * * Klasa zarz¹dza wspóln¹ logik¹ dla wszystkich typów potworów, w tym
 * systemem poruszania siê po œcie¿ce (Path Following) oraz wyœwietlaniem pasków zdrowia.
 */
class Monster
{
public:
    // Wirtualny destruktor gwarantuje poprawne czyszczenie zasobów klas pochodnych
    virtual ~Monster() = default;

    // --- Atrybuty kondycji i ekonomii ---
    float mMaxHP;           // Maksymalna wytrzyma³oœæ jednostki
    float mHP;              // Aktualny stan punktów ¿ycia
    int mDamage;            // Kara nak³adana na HP gracza po dotarciu do celu
    int mGold;              // Nagroda finansowa dla gracza za eliminacjê jednostki
    float mSpeed;           // Prêdkoœæ przemieszczania siê wyra¿ona w pikselach na sekundê
    sf::Color normalColor;
    // --- Logika nawigacji i statusu ---
    int pathIndex = 0;      // Indeks punktu (waypoint), do którego obecnie zmierza jednostka
    bool reachedEnd = false;// Flaga aktywowana po dotarciu do ostatniego punktu œcie¿ki
    bool isDead = false;    // Flaga eliminacji (HP <= 0) wyzwalaj¹ca usuniêcie z pamiêci
    enum class StatusEffect
    {
        None,
        Slow,
        Stun
    };
    struct ActiveEffect
    {
        StatusEffect type;
        float duration;
        float value; 
    };
    vector<ActiveEffect> effects;

    float baseSpeed;
    bool isStunned = false;

    void ApplyEffect(StatusEffect type, float duration, float value);
    void UpdateEffects(float dt);
    bool HasEffect(StatusEffect type);
    // --- Komponenty wizualne (Renderable Components) ---
    sf::RectangleShape shape;           // G³ówny korpus potwora
    sf::RectangleShape hpBarBackground; // T³o paska zdrowia (zazwyczaj czerwone/czarne)
    sf::RectangleShape hpBarFill;       // Wype³nienie paska zdrowia (dynamicznie skalowane)

    // --- Metody cyklu ¿ycia i logiki ---

    /**
     * @brief Przetwarza ruch w stronê kolejnych punktów œcie¿ki.
     * @param dt Czas od ostatniej klatki (Delta Time).
     * @param path Wektor punktów Vector2f definiuj¹cy trasê przemarszu.
     */
    virtual void Update(float dt, const vector<sf::Vector2f>& path);

    /**
     * @brief Renderuje potwora wraz z jego interfejsem (paskiem zdrowia).
     */
    virtual void Draw(sf::RenderWindow& window);

    /**
     * @brief Aktualizuje szerokoœæ paska zdrowia na podstawie stosunku mHP/mMaxHP.
     */
    virtual void ChangeHpBar();

protected:
    /**
     * @brief Konstruktor chroniony – wywo³ywany wy³¹cznie przez klasy pochodne.
     * @param startPos Wspó³rzêdne pierwszego punktu œcie¿ki (spawn point).
     */
    Monster(sf::Vector2f startPos);
};