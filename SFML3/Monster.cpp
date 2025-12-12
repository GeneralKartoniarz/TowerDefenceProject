#include "Monster.h"

Monster::Monster(int hp, float speed, int damage, int gold, std::string name, sf::Texture texture) {
	mHP = hp;
	mSpeed = speed;
	mDamage = damage;
	mGold = gold;
	mName = name;
	mTexture = texture;
}
int Monster::getHP() {
    return mHP;
}

void Monster::setHP(int hp) {
    mHP = hp;
}

float Monster::getSpeed() {
    return mSpeed;
}

void Monster::setSpeed(float speed) {
    mSpeed = speed;
}

int Monster::getDamage() {
    return mDamage;
}

void Monster::setDamage(int damage) {
    mDamage = damage;
}

int Monster::getGold() {
    return mGold;
}

void Monster::setGold(int gold) {
    mGold = gold;
}

std::string Monster::getName() {
    return mName;
}

void Monster::setName(std::string name) {
    mName = name;
}

sf::Texture Monster::getTexture() {
    return mTexture;
}

void Monster::setTexture(sf::Texture texture) {
    mTexture = texture;  
}
