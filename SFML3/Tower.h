#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class Tower
{
public:
	//konstruktor
	Tower(int cost, float attack, float range,string name, sf::Texture texture);
	
	int tCost;
	float tAttack;
	float tRange;
	string tName;
	sf::Texture tTexture;
	sf::RectangleShape tShape;
private:

};

