#include "Tile.h"
#include <vector>



void Tile::Draw(sf::RenderWindow& window) {
	window.draw(shape);
}
Tile::Tile(sf::Vector2f position, float size)
	: size(size)
{
	shape.setSize({ size, size });
	shape.setOrigin({ size / 2.f, size / 2.f });
	shape.setPosition(position);
	shape.setFillColor(normalColor);
}

Tile::~Tile()
{

}

void Tile::SetPosition(float x, float y) {
	shape.setPosition({ x,y });
}
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
	if (IsMouseOver(mouseX, mouseY) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		return true;
	else
		return false;
}