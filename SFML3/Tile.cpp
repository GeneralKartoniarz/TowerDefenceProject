#include "Tile.h"
#include <vector>



void Tile::Draw(sf::RenderWindow& window) {
	window.draw(shape);
}
void Tile::Refresh()
{
	if (this->state == TileState::Placement)
		this->shape.setFillColor(normalColor);
	else if (this->state == TileState::Path)
		this->shape.setFillColor(sf::Color(186, 153, 99));
	else
		this->shape.setFillColor(sf::Color(201, 104, 77));
}
Tile::Tile(sf::Vector2f position, float size, TileState state)
	: size(size)
{
	this->state = state;
	shape.setSize({ size, size });
	shape.setOrigin({ size / 2.f, size / 2.f });
	shape.setPosition(position);
	Refresh();

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