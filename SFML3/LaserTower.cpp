#include "LaserTower.h"
#include "Bullet.h"
#include <cmath>

using namespace std;

/**
 * @brief Konstruktor LaserTower.
 * Definiuje profil bojowy wie¿y laserowej, ustawiaj¹c parametry zasiêgu i szybkoœci ognia.
 */
LaserTower::LaserTower(sf::Vector2f position)
{
    // --- Konfiguracja parametrów bojowych ---
    tCost = COST;
    tAttack = 0.2f;       // Obra¿enia zadawane przez pojedynczy pocisk
    tRange = 200.f;       // Promieñ skanowania celów
    tName = "Laser Tower";

    // Bardzo niski cooldown sugeruje wie¿ê typu "rapid fire" lub b³¹d w skali dt.
    // Wartoœæ 0.0008f przy dt (np. 1/60s) oznacza strza³ niemal w ka¿dej klatce.
    attackCooldown = 0.0008f;
    attackTimer = 0.f;

    // --- Konfiguracja reprezentacji graficznej ---
    tShape.setSize({ 50.f, 50.f });
    tShape.setOrigin(tShape.getSize() / 2.f); // Centrowanie punktu rotacji i pozycji
    tShape.setFillColor(sf::Color::Yellow);   // Kolor identyfikuj¹cy typ wie¿y
    tShape.setPosition(position);
}

/**
 * @brief Logika operacyjna wie¿y.
 * Przetwarza cykl ³adowania broni oraz przeszukuje obszar w poszukiwaniu najbli¿szego potwora.
 */
void LaserTower::Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets)
{
    // Obs³uga licznika prze³adowania (Cooldown)
    attackTimer += dt;
    if (attackTimer < attackCooldown)
        return;

    Monster* target = nullptr;
    float closestDistance = tRange; // Inicjalizacja maksymalnym zasiêgiem

    // --- Algorytm wyboru celu (Nearest Target) ---
    // Przeszukiwanie kontenera potworów w celu znalezienia obiektu najbli¿szego wie¿y.
    for (auto& monster : monsters)
    {
        sf::Vector2f mPos = monster->shape.getPosition();
        sf::Vector2f tPos = tShape.getPosition();

        // Obliczanie dystansu euklidesowego miêdzy wie¿¹ a potworem
        float dx = mPos.x - tPos.x;
        float dy = mPos.y - tPos.y;
        float dist = sqrt(dx * dx + dy * dy);

        // Jeœli potwór jest w zasiêgu i jest bli¿ej ni¿ poprzednio znaleziony
        if (dist <= closestDistance)
        {
            closestDistance