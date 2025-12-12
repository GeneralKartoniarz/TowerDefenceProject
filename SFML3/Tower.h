#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Tower
{
public:
	//konstruktor
	Tower(int cost, float attack, float range,std::string name, sf::Texture texture);
	
	int getCost();
	void setCost(int cost);

	float getAttack();
	void setAttack(float attack);

	float getRange();
	void setRange(float range);

	std::string getName();
	void setName(std::string name);

	sf::Texture getTexture();
	void setTexture(sf::Texture texture);

private:
	//w³asnoœci objektu

	int tCost;
	float tAttack;
	float tRange;
	std::string tName;
	sf::Texture tTexture;

};

