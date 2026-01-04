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
	enum class TileState
	{
		Path,
		Placement,
		Locked
	};
	sf::RectangleShape shape;
	float size = 50.f;
	sf::Color normalColor = sf::Color::Blue;

	TileState state;
	Tile(sf::Vector2f position, float size,TileState state);
	~Tile();

	void SetPosition(float x, float y);
	bool IsMouseOver(float mouseX, float mouseY);
	bool IsButtonClicked(float mouseX, float mouseY);
	void Draw(sf::RenderWindow& window);
private:
};

