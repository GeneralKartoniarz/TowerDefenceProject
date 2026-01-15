#include "Tile.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

// Inicjalizacja statycznej puli œcie¿ek do tekstur terenu
vector<string> Tile::placementPaths =
{
    "assets/mapa1.png",
    "assets/mapa2.png",
    "assets/mapa3.png",
    "assets/mapa4.png",
    "assets/mapa5.png"
};

/**
 * @brief Zarz¹dza teksturami kafelka.
 * * Wybiera losow¹ teksturê z puli dostêpnych grafik terenu, co pozwala
 * na unikniêcie wizualnej powtarzalnoœci siatki (gridu).
 */
void Tile::LoadTexture(const string& path)
{
    int r = rand() % placementPaths.size();
    if (!texture.loadFromFile(placementPaths[r]))
    {
        cout << "B³¹d krytyczny: Nie za³adowano tekstury: " << placementPaths[r] << endl;
    }
    shape.setTexture(&texture);
}

Tile::Tile(sf::Vector2f position, float size, TileState state)
    : size(size)
{
    this->state = state;

    // Konfiguracja geometrii: ustawienie rozmiaru i wycentrowanie punktu zakotwiczenia
    shape.setSize({ size, size });
    shape.setOrigin({ size / 2.f, size / 2.f });
    shape.setPosition(position);

    // Pierwsza synchronizacja wygl¹du ze stanem logicznym
    Refresh();
}

Tile::~Tile()
{
    // Destruktor domyœlny
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

/**
 * @brief Maszyna stanów wizualnych kafelka.
 * * Dopasowuje oprawê graficzn¹ (kolor lub teksturê) do roli kafelka w grze.
 * Wywo³ywana przy inicjalizacji oraz przy zmianie typu kafelka (np. po zabudowaniu).
 */
void Tile::Refresh()
{
    if (this->state == TileState::Placement)
    {
        // Pola do zabudowy otrzymuj¹ teksturê i pe³n¹ nieprzezroczystoœæ
        LoadTexture("assets/mapa1.png");
        this->shape.setFillColor(sf::Color(255, 255, 255, 255));
    }
    else if (this->state == TileState::Path)
    {
        // Œcie¿ka potworów oznaczona ciemniejszym kolorem dla kontrastu
        this->shape.setFillColor(sf::Color(43, 43, 43));
    }
    else // TileState::Locked
    {
        // Pola zajête lub zablokowane otrzymuj¹ odcieñ ceglasty/ostrzegawczy
        this->shape.setFillColor(sf::Color(201, 104, 77));
    }
}

void Tile::SetPosition(float x, float y)
{
    shape.setPosition({ x, y });
}

/**
 * @brief Test kolizji punkt-prostok¹t (Point vs AABB).
 * * Uwzglêdnia fakt, ¿e origin kafelka znajduje siê w jego œrodku,
 * dlatego granice s¹ obliczane jako [pozycja +/- po³owa rozmiaru].
 */
bool Tile::IsMouseOver(float mouseX, float mouseY)
{
    sf::Vector2f sp = shape.getPosition();
    sf::Vector2f sh = shape.getSize() / 2.f;

    return
        mouseX >= sp.x - sh.x &&
        mouseX <= sp.x + sh.x &&
        mouseY >= sp.y - sh.y &&
        mouseY <= sp.y + sh.y;
}

bool Tile::IsButtonClicked(float mouseX, float mouseY)
{
    bool isHover = IsMouseOver(mouseX, mouseY);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // Detekcja pojedynczego klikniêcia (zbocze narastaj¹ce)
    bool clicked = isHover && isPressed && !wasPressed;

    // Aktualizacja stanu przycisku dla nastêpnej klatki (debouncing)
    wasPressed = isPressed;

    return clicked;
}