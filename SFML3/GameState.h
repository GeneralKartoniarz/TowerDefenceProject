#pragma once
#include "States.h"
#include "Button.h"
#include "Tile.h"
#include <vector>
using namespace std;
class GameState :
    public States
{
public:
    GameState(sf::RenderWindow* windowPtr);
    ~GameState();
    float screenWidth;
    float screenHeight;

    int tileSize = 96;
    int columns = 19;
    int rows = 9;
    int spacing = 0;
    int selectedTile;
    
    bool isTileSelected = false;

    vector<Tile> tiles;
    vector<Button> buttons;

    sf::Font fontGameState;

    void EndState();
    void QuitCheck();
    void Update(float dt);
    void Render(sf::RenderWindow* windowPtr);
private:

};

