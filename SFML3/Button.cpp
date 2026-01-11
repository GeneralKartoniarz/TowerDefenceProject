#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// --- KONSTRUKTOR ---
// Inicjalizuje kszta³t, tekst oraz ustawia pocz¹tkowe wyœrodkowanie
Button::Button(sf::Font& font) : text(font)
{
    this->shape.setSize(this->size);
    this->shape.setOrigin(shape.getLocalBounds().position + shape.getLocalBounds().size / 2.f);
    this->shape.setPosition(this->position);
    this->text.setString(defText);

    CenterText();
}

// --- DESTRUKTOR ---
Button::~Button()
{
}

// --- RENDEROWANIE ---
// Rysuje najpierw t³o przycisku, a nastêpnie tekst na wierzchu
void Button::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
}

// --- TRANSFORMACJE I POZYCJONOWANIE ---
// Ustawia now¹ pozycjê przycisku i automatycznie przesuwa tekst
void Button::SetPosition(float x, float y) {
    shape.setPosition({ x, y });
    CenterText();
}

// Wyœrodkowuje tekst wzglêdem aktualnej pozycji i wymiarów kszta³tu
void Button::CenterText()
{
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.position + tb.size / 2.f);
    text.setPosition(shape.getPosition());
}

// --- INTERAKCJA I LOGIKA MYSZY ---
// Sprawdza, czy kursor znajduje siê wewn¹trz granic przycisku
bool Button::IsMouseOver(float mouseX, float mouseY)
{
    sf::Vector2f sp = shape.getPosition();
    sf::Vector2f sh = shape.getSize() / 2.f;

    return
        mouseX >= sp.x - sh.x &&
        mouseX <= sp.x + sh.x &&
        mouseY >= sp.y - sh.y &&
        mouseY <= sp.y + sh.y;
}

// Sprawdza, czy przycisk jest najechany i jednoczeœnie klikniêty lewym przyciskiem myszy
bool Button::IsButtonClicked(float mouseX, float mouseY)
{
    bool isHover = IsMouseOver(mouseX, mouseY);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    bool clicked = isHover && isPressed && !wasPressed;

    wasPressed = isPressed;

    return clicked;
}

// Aktualizuje kolor przycisku w zale¿noœci od tego, czy mysz nad nim widnieje
void Button::UpdateHover(float mouseX, float mouseY)
{
    shape.setFillColor(IsMouseOver(mouseX, mouseY) ? hoverColor : normalColor);
}