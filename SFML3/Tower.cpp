#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <string>
Tower::Tower(int cost, float attack, float range, std::string name, sf::Texture texture) {
	tCost = cost;
	tAttack = attack;
	tRange = range;
	tName = name;
	tTexture = texture;
}
int Tower::getCost() {
    return tCost;
}

void Tower::setCost(int cost) {
    tCost = cost;
}

float Tower::getAttack() {
    return tAttack;
}

void Tower::setAttack(float attack) {
    tAttack = attack;
}

float Tower::getRange() {
    return tRange;
}

void Tower::setRange(float range) {
    tRange = range;
}

std::string Tower::getName() {
    return tName;
}

void Tower::setName(std::string name) {
    tName = name;
}

sf::Texture Tower::getTexture() {
    return tTexture;   
}

void Tower::setTexture(sf::Texture texture) {
    tTexture = texture;
}
