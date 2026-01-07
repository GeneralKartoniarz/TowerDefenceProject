#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
#include <vector>
using namespace std;
class Game
{
public:
	//konstruktor i destruktor
	Game();
	~Game();
	//metody
	void InitWindow();
	void UpdateEvent();
	void Update(float dt);
	void Render();
	void Run();
	void InitStates();


private:
	//zmienne i wskaüniki
	sf::Clock dtClock;
	float dt;
	sf::RenderWindow* windowPtr;
	optional<sf::Event> ev;
	vector<States*> states;;
	int activeState;
};

