#pragma once
#include "States.h"
#include "Button.h"
#include "Tile.h"
#include "Tower.h"
#include "Monster.h"
#include <vector>
using namespace std;
class GameState :
    public States
{
public:
    GameState(sf::RenderWindow* windowPtr, int difficulty);
    ~GameState();
    float screenWidth;
    float screenHeight;

    int difficulty;
    int tileSize = 96;
    int columns = 19;
    int rows = 9;
    int spacing = 0;
    int selectedTile;
    int selectedTower;
    int currentWave = 1;
    int waves = 50;
    int monsterPerWave = 20;
    bool isTileSelected = false;
    int playerGold = 2000;
    int playerHp = 100;
    int currentTurn = 1;
    float spawnTimer = 0.f;
    float spawnDelay = .5f;

    vector<Tile> tiles;
    vector<Button> buttons;
    vector<Monster> monsters;
    vector<Tower> towers;
    vector<int> map;
    vector<sf::Vector2f> pathPoints;


    sf::Font fontGameState;
    
    sf::RectangleShape hpBox;
    sf::RectangleShape goldBox;
    sf::RectangleShape turnBox;
    
    sf::Text hpText;
    sf::Text goldText;
    sf::Text turnText;

    void EndState();
    void QuitCheck();
    void Update(float dt);
    void Render(sf::RenderWindow* windowPtr);

private:

};

