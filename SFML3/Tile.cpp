#include "Tile.h"
#include <vector>

// --- Konstruktor ---
// Ustawia parametry pocz¹tkowe, rozmiar, punkt œrodka (origin) i odœwie¿a kolor
Tile::Tile(sf::Vector2f position, float size, TileState state)
    : size(size)
{
    this->state = state;
    shape.setSize({ size, size });
    shape.setOrigin({ size / 2.f, size / 2.f });
    shape.setPosition(position);
    Refresh();
}

// --- Destruktor ---
Tile::~Tile()
{
}

// --- Renderowanie ---
// Rysuje kszta³t kafelka w podanym oknie
void Tile::Draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// --- Logika Wygl¹du ---
// Aktualizuje kolor kafelka w zale¿noœci od jego stanu (Placement, Path lub Locked)
void Tile::Refresh()
{
    if (this->state == TileState::Placement)
        this->shape.setFillColor(normalColor);
    else if (this->state == TileState::Path)
        this->shape.setFillColor(sf::Color(186, 153, 99));
    else
        this->shape.setFillColor(sf::Color(201, 104, 77));
}

// --- Transformacje ---
// Ustawia now¹ pozycjê kafelka na mapie
void Tile::SetPosition(float x, float y) {
    shape.setPosition({ x, y });
}

// --- Interakcja ---
// Sprawdza, czy wspó³rzêdne myszy zawieraj¹ siê w obszarze kafelka
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

// Sprawdza, czy mysz jest nad kafelkiem i czy lewy przycisk jest wciœniêty
bool Tile::IsButtonClicked(float mouseX, float mouseY)
{
    bool isHover = IsMouseOver(mouseX, mouseY);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    bool clicked = isHover && isPressed && !wasPressed;

    wasPressed = isPressed;

    return clicked;
}