#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Monster
{
public:
	//konstruktor
	Monster(int hp, float speed, int damage, int gold, std::string name ,sf::Texture texture);
	
	//gettery i settery
	int getHP();
	void setHP(int mHP);

	float getSpeed();
	void setSpeed(float mSpeed);

	int getDamage();
	void setDamage(int mDamage);

	int getGold();
	void setGold(int mGold);

	std::string getName();
	void setName(std::string mName);

	sf::Texture getTexture();
	void setTexture(sf::Texture texture);


private:
	//w³asnoœci objektu
	
	int mHP;
	float mSpeed;
	int mDamage;
	int mGold;
	std::string mName;
	sf::Texture mTexture;
};

