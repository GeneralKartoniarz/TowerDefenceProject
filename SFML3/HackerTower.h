#pragma once
#include "Tower.h"
#include <string>
using namespace std;
class HackerTower : public Tower
{
public:
    static constexpr int COST = 500;

    HackerTower(sf::Vector2f position);
    string path = "hacker";
    void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) override;
    void Draw(sf::RenderWindow& window) override;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
private:

};

