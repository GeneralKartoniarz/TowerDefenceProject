#pragma once
#include <iostream>   
#include <string>   
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
class Tile
{
public:
	sf::RectangleShape shape;
	float size = 50.f;
	sf::Color normalColor = sf::Color::Blue;
	enum tileState
	{
		path,
		placement,
		locked
	};

	Tile(sf::Vector2f position, float size);
	~Tile();

	void SetPosition(float x, float y);
	bool IsMouseOver(float mouseX, float mouseY);
	bool IsButtonClicked(float mouseX, float mouseY);
	void Draw(sf::RenderWindow& window);
private:
};

