#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class Tower
{
public:
	//konstruktor
	Tower(int cost, float attack, float range,string name, sf::Texture texture);
	
	int getCost();
	void setCost(int cost);

	float getAttack();
	void setAttack(float attack);

	float getRange();
	void setRange(float range);

	string getName();
	void setName(string name);

	sf::Texture getTexture();
	void setTexture(sf::Texture texture);

private:
	//w³asnoœci objektu

	int tCost;
	float tAttack;
	float tRange;
	string tName;
	sf::Texture tTexture;

};

