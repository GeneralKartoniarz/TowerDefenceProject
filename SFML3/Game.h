#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
class Game
{
public:
	//konstruktor i destruktor
	Game();
	~Game();
	//metody
	void InitWindow();
	void UpdateEvent();
	void Update();
	void Render();
	void Run();


private:
	//zmienne i wskaüniki
	sf::RenderWindow* window;
	std::optional<sf::Event> ev;
};

