#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "States.h"
#include "GameState.h"
#include <stack>
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
	void Update();
	void Render();
	void Run();
	void InitStates();
	void ChangeState(States* newState);
	void PushState(States* newState);
	void PopState();


private:
	//zmienne i wskaüniki
	sf::RenderWindow* windowPtr;
	optional<sf::Event> ev;
	stack<States*> state;
};

