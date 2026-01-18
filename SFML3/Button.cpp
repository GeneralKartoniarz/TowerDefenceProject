#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

void Button::LoadTexture(const string& path)
{
    if (!texture.loadFromFile(path))
    {
        cout << "B³¹d krytyczny: Nie za³adowano tekstury: " << path << endl;
    }
    shape.setTexture(&texture);
}
Button::Button(sf::Font& font) : text(font)
{
    // Konfiguracja bazowej geometrii prostok¹ta
    this->shape.setSize(this->size);

    // Ustawienie punktu kotwiczenia (origin) na geometrycznym œrodku prostok¹ta
    this->shape.setOrigin(shape.getLocalBounds().position + shape.getLocalBounds().size / 2.f);
    this->shape.setPosition(this->position);

    // Przypisanie domyœlnej treœci etykiety
    this->text.setString(defText);

    // Wstêpne wyrównanie tekstu do œrodka przycisku
    CenterText();
}

Button::~Button()
{
    // Destruktor domyœlny
}

void Button::Draw(sf::RenderWindow& window)
{
    // Renderowanie warstwowe: najpierw t³o, potem etykieta tekstowa
    window.draw(shape);
    window.draw(text);
}

void Button::SetPosition(float x, float y) {
    // Aktualizacja wspó³rzêdnych przycisku i wymuszenie rekalkulacji pozycji tekstu
    shape.setPosition({ x, y });
    CenterText();
}

void Button::CenterText()
{
    // Obliczanie œrodka lokalnego tekstu i ustawienie go jako punktu odniesienia
    sf::FloatRect tb = text.getLocalBounds();
    text.setOrigin(tb.position + tb.size / 2.f);

    // Synchronizacja pozycji tekstu z pozycj¹ kszta³tu (oba maj¹ origin w œrodku)
    text.setPosition(shape.getPosition());
}

bool Button::IsMouseOver(float mouseX, float mouseY)
{
    // Pobranie aktualnego stanu transformacji kszta³tu
    sf::Vector2f sp = shape.getPosition();
    sf::Vector2f sh = shape.getSize() / 2.f;

    // Test kolizji punktu z obszarem typu AABB (Axis-Aligned Bounding Box)
    return
        mouseX >= sp.x - sh.x &&
        mouseX <= sp.x + sh.x &&
        mouseY >= sp.y - sh.y &&
        mouseY <= sp.y + sh.y;
}

bool Button::IsButtonClicked(float mouseX, float mouseY)
{
    // Sprawdzenie stanu najechania i fizycznego naciœniêcia klawisza myszy
    bool isHover = IsMouseOver(mouseX, mouseY);
    bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // Detekcja zbocza narastaj¹cego (zapobiega wielokrotnemu wyzwalaniu przy trzymaniu przycisku)
    bool clicked = isHover && isPressed && !wasPressed;

    // Zapamiêtanie stanu do porównania w kolejnej klatce (debouncing)
    wasPressed = isPressed;

    return clicked;
}

void Button::UpdateHover(float mouseX, float mouseY)
{
    // Dynamiczna zmiana barwy wype³nienia w oparciu o pozycjê kursora
    shape.setFillColor(IsMouseOver(mouseX, mouseY) ? hoverColor : normalColor);
}