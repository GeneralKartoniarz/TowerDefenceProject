#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;
// --- KLASA BAZOWA POTWORA (ABSTRAKCYJNA) ---
// Odpowiada za wspóln¹ logikê ruchu i podstawowe statystyki
class Monster
{
public:
    // --- Destruktor wirtualny ---
    // Wymagany przy dziedziczeniu (unique_ptr, delete przez wskaŸnik)
    virtual ~Monster() = default;

    // --- Statystyki potwora ---
    float mMaxHP;         // Maksymalne punkty ¿ycia
    float mHP;            // Punkty ¿ycia
    int mDamage;        // Obra¿enia zadawane bazie
    int mGold;          // Z³oto za zabicie
    float mSpeed;       // Prêdkoœæ poruszania

    // --- Logika œcie¿ki ---
    int pathIndex = 0;  // Aktualny punkt na œcie¿ce
    bool reachedEnd = false; // Czy dotar³ do koñca mapy
    bool isDead = false; // Czy dotar³ do koñca mapy KILLER IS DEAD ZNACZY ¯E JA GO KYLLYM

    // --- Grafika ---
    sf::RectangleShape shape; // Reprezentacja wizualna potwora
    sf::RectangleShape hpBarBackground;
    sf::RectangleShape hpBarFill;
    // --- Metody g³ówne ---
    // Aktualizuje ruch potwora po œcie¿ce
    virtual void Update(float dt, const vector<sf::Vector2f>& path);
    // Rysuje potwora w oknie gry
    virtual void Draw(sf::RenderWindow& window);
    virtual void ChangeHpBar();
protected:
    // --- Konstruktor chroniony ---
    // Zapobiega tworzeniu obiektu Monster bezpoœrednio
    Monster(sf::Vector2f startPos);
};
