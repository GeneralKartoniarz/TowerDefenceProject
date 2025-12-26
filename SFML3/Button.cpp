#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
Button::Button(sf::Font& font) :text(font) {
	this->shape.setSize(this->size);
	this->shape.setOrigin(shape.getLocalBounds().position + shape.getLocalBounds().size / 2.f);
	this->shape.setPosition(this->position);
	this->text.setString(defText);
	
	CenterText();
	
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}
void Button::CenterText()
{
	sf::FloatRect tb = text.getLocalBounds();
	text.setOrigin(tb.position + tb.size / 2.f);
	text.setPosition(shape.getPosition());
}
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
bool Button::IsButtonClicked(float mouseX, float mouseY)
{
	if(IsMouseOver(mouseX,mouseY)&&(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)))
		return true;
	else
		return false;
}
void Button::SetPosition(float x, float y) {
	shape.setPosition({ x,y });
	CenterText();
}