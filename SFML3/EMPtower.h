#pragma once
#include "Tower.h"
using namespace std;
class EMPtower : public Tower
{
public:
    static const int COST = 150;
    EMPtower(sf::Vector2f pos);
    string path = "emp";
    void Update(float dt, vector<unique_ptr<Monster>>& monsters,vector<unique_ptr<Bullet>>& bullets) override;
    void Draw(sf::RenderWindow& window) override;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
private:

};
