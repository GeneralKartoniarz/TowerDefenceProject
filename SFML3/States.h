#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <stack>
#include<string>

class States
{
public:
	sf::RenderWindow* windowPtr;
	States(sf::RenderWindow* windowPtr);
	virtual ~States();

	bool quit;

	void CheckForQuit();
	bool GetQuit();
	virtual void EndState() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow* windowPtr) = 0;
private:
};

