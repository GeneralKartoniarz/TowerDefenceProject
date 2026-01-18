#include "LaserTower.h"
#include "Bullet.h"
#include <cmath>

using namespace std;

/**
 * @brief Konstruktor LaserTower.
 * Definiuje profil bojowy wie¿y laserowej, ustawiaj¹c parametry zasiêgu i szybkoœci ognia.
 */
LaserTower::LaserTower(sf::Vector2f position):shootSound(shootBuffer)
{
    LoadTexture("assets/laser_tower/inferno1.png");
    // --- Konfiguracja parametrów bojowych ---
    tCost = COST;
    tAttack = 0.2f;       // Obra¿enia zadawane przez pojedynczy pocisk
    tRange = 200.f;       // Promieñ skanowania celów
    tName = "Laser Tower";
    cooldownCounter = 0;
    cooldownTime = 3.f;
    heat = 0;
    heatMax = 6.f;
    // Bardzo niski cooldown sugeruje wie¿ê typu "rapid fire" lub b³¹d w skali dt.
    // Wartoœæ 0.0008f przy dt (np. 1/60s) oznacza strza³ niemal w ka¿dej klatce.
    attackCooldown = 0.0008f;
    attackTimer = 0.f;

    if (!shootBuffer.loadFromFile("assets/sfx/laserSound.wav"))
        cout << "c";
    shootSound.setVolume(40.f);

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
    if (heat >= heatMax) {
        cooldownCounter += dt;
        if (cooldownCounter >= cooldownTime) {
            heat = 0;
            cooldownCounter = 0;
        }

        return;
    }

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
            closestDistance = dist;
            target = monster.get(); // Pobranie surowego wskaŸnika do obserwacji celu
        }
    }

    // --- Procedura generowania strza³u ---
    // Jeœli znaleziono cel w zasiêgu, instancjonowany jest nowy pocisk zmierzaj¹cy do celu.
    if (target)
    {
        RotateToEnemy(target);
        // Utworzenie inteligentnego wskaŸnika na pocisk i dodanie go do globalnej listy w GameState
        bullets.push_back(make_unique<Bullet>(tShape.getPosition(), target, 1200.f, tAttack, 0.f,monsters));
        shootSound.play();
        // Resetowanie licznika czasu do zera (inicjacja prze³adowania)
        attackTimer = 0.f;
        heat += dt;

    }

}

/**
 * @brief Przesy³a kszta³t wie¿y do bufora ramki okna.
 */
void LaserTower::Draw(sf::RenderWindow& window)
{
    window.draw(tShape);
    if (isRangeShown) {
        sf::CircleShape rangeCircle(this->tRange);
        rangeCircle.setOrigin({ this->tRange, this->tRange });
        rangeCircle.setPosition(this->tShape.getPosition());
        rangeCircle.setFillColor(sf::Color(250, 50, 50, 100));
        window.draw(rangeCircle);
    }
}