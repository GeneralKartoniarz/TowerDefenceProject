#pragma once
#include "Monster.h"
class Boss : public Monster
{
public:
	Boss(sf::Vector2f startPos);
	void ChangeHpBar();
	sf::Texture texture;            
	void LoadTexture(const string& path);
};

