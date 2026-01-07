#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// --- KLASA BAZOWA POTWORA (ABSTRAKCYJNA) ---
// Odpowiada za wspóln¹ logikê ruchu i podstawowe statystyki
class Monster
{
public:
    // --- Destruktor wirtualny ---
    // Wymagany przy dziedziczeniu (unique_ptr, delete przez wskaŸnik)
    virtual ~Monster() = default;

    // --- Statystyki potwora ---
    int mMaxHP;         // Maksymalne punkty ¿ycia
    int mHP;            // Punkty ¿ycia
    int mDamage;        // Obra¿enia zadawane bazie
    int mGold;          // Z³oto za zabicie
    float mSpeed;       // Prêdkoœæ poruszania

    // --- Logika œcie¿ki ---
    int pathIndex = 0;  // Aktualny punkt na œcie¿ce
    bool reachedEnd = false; // Czy dotar³ do koñca mapy

    // --- Grafika ---
    sf::RectangleShape shape; // Reprezentacja wizualna potwora
    sf::RectangleShape hpBarBackground;
    sf::RectangleShape hpBarFill;
    // --- Metody g³ówne ---
    // Aktualizuje ruch potwora po œcie¿ce
    virtual void Update(float dt, const std::vector<sf::Vector2f>& path);

    // Rysuje potwora w oknie gry
    virtual void Draw(sf::RenderWindow& window);
    virtual void ChangeHpBar();
protected:
    // --- Konstruktor chroniony ---
    // Zapobiega tworzeniu obiektu Monster bezpoœrednio
    Monster(sf::Vector2f startPos);
};
