#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>   
#include <string>
using namespace std;
class Button
{
public:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Vector2f size = { 200.f,100.f };
	sf::Vector2f position;
	string defText = "Test Button";

	Button(sf::Font &font);
	~Button();
	void Draw(sf::RenderWindow& window);
	void SetPosition(float x, float y);
	void CenterText();
	bool IsMouseOver(float mouseX, float mouseY);
	bool IsButtonClicked(float mouseX, float mouseY);
};

