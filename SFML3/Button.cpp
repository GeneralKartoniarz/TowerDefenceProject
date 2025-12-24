#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

Button::Button(sf::Font& font):text(font) {
	this->shape.setScale(this->size);
	this->shape.setPosition(this->position);
	this->text.setString(defText);
}

Button::~Button()
{
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}
