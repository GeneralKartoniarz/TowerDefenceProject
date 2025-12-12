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
	void setHP(int hp);

	float getSpeed();
	void setSpeed(float speed);

	int getDamage();
	void setDamage(int damage);

	int getGold();
	void setGold(int gold);

	std::string getName();
	void setName(std::string name);

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

