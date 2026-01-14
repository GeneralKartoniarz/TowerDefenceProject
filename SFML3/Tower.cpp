#include "Tower.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
void Tower::LoadTexture(const string& path)
{
    if (!texture.loadFromFile(path))
        cout << "Nie zaladowano tekstury: " << path;

    tShape.setTexture(&texture);
}