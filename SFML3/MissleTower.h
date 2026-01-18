#pragma once
#include "Tower.h"
#include <string>
class MissleTower : public Tower
{
public:
    static constexpr int COST = 500;

    MissleTower(sf::Vector2f position);
    string path = "miss";
    void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) override;
    void Draw(sf::RenderWindow& window) override;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
private:

};

