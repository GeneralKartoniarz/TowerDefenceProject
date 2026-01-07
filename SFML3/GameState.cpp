#include "GameState.h"   
#include "MainMenuState.h"   
#include "States.h"           
#include "Tile.h"           
#include "Button.h"      
#include "Monster.h"      
#include "Tower.h"      
#include <iostream>   
#include <string>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;  

GameState::GameState(sf::RenderWindow* windowPtr, int difficulty)
    : States(windowPtr),hpText(fontGameState),goldText(fontGameState),turnText(fontGameState)
{
    ifstream mapFile; 
    mapFile.open("map.txt");
    string mapString;
    string tempString;
    while (getline(mapFile, tempString)) {
        mapString += tempString;
    }
    for (int i = 0; i < mapString.length(); i++)
    {
        map.push_back(mapString.at(i));
    }
    if (!fontGameState.openFromFile("comicFont.ttf")) {
        cout << "Font sie zepsul";
    }
    srand(time(0));
    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;
    this->difficulty = difficulty;

    tiles.clear();
    tiles.reserve(columns * rows);
    
    float gridWidth = columns * tileSize + (columns - 1) * spacing;
    
    float gridHeight = rows * tileSize + (rows - 1) * spacing;
    
    sf::Vector2f offset((screenWidth - gridWidth) / 2.f + tileSize / 2.f, screenHeight - gridHeight + tileSize / 2.f-40);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int currentTile = i * columns + j;

            sf::Vector2f position(offset.x + j * (tileSize + spacing),
                offset.y + i * (tileSize + spacing));

            Tile::TileState state;
            char type = mapString[currentTile];

            if (type == '1')      
                state = Tile::TileState::Path;
            else if (type == '2') 
                state = Tile::TileState::Locked;
            else                  
                state = Tile::TileState::Placement;
            tiles.emplace_back(position, tileSize, state);
            tiles.back().Refresh();
        }

    }
    pathPoints.clear();

    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].state == Tile::TileState::Path)
        {
            pathPoints.push_back(tiles[i].shape.getPosition());
        }
    }
    int buttonCount = 6;
    float buttonSpacing = 20.f;
    float topMargin = 15.f;
    buttons.clear();
    buttons.reserve(buttonCount);

    for (int i = 0; i < buttonCount; i++)
    {
        buttons.emplace_back(fontGameState);
    }

    float buttonWidth = buttons[0].shape.getSize().x;
    float buttonHeight = buttons[0].shape.getSize().y;

    float totalWidth = buttonCount * buttonWidth + (buttonCount - 1) * buttonSpacing;

    float startX = (screenWidth - totalWidth) / 2.f + buttonWidth / 2.f;
    float y = topMargin + buttonHeight / 2.f;

    for (int i = 0; i < buttonCount; i++)
    {
        buttons[i].defText = to_string(i);
        buttons[i].text.setString(buttons[i].defText);

        buttons[i].normalColor = sf::Color(255, 222, 89);
        buttons[i].hoverColor = sf::Color(255, 200, 0);
        buttons[i].shape.setFillColor(buttons[i].normalColor);

        float x = startX + i * (buttonWidth + buttonSpacing);
        buttons[i].SetPosition(x, y);
    }
    mapFile.close();

    float boxWidth = 160.f;
    float boxHeight = 40.f;
    float margin = 20.f;

   
    hpBox.setSize({ boxWidth, boxHeight });
    hpBox.setFillColor(sf::Color(40, 40, 40));
    hpBox.setOutlineThickness(2.f);
    hpBox.setOutlineColor(sf::Color::White);
    hpBox.setPosition({ margin, margin });

    
    goldBox = hpBox;
    goldBox.setPosition({ margin, margin + boxHeight + 5 });

    turnBox = hpBox;
    turnBox.setPosition({ margin, margin + 2 * (boxHeight + 5) });

    hpText.setFont(fontGameState);
    goldText.setFont(fontGameState);
    turnText.setFont(fontGameState);



    hpText.setCharacterSize(18);
    goldText.setCharacterSize(18);
    turnText.setCharacterSize(18);

    hpText.setFillColor(sf::Color::White);
    goldText.setFillColor(sf::Color::White);
    turnText.setFillColor(sf::Color::White);

    hpText.setPosition(hpBox.getPosition() + sf::Vector2f(8, 8));
    goldText.setPosition(goldBox.getPosition() + sf::Vector2f(8, 8));
    turnText.setPosition(turnBox.getPosition() + sf::Vector2f(8, 8));







}

GameState::~GameState() {

}

void GameState::EndState() {

}

void GameState::QuitCheck()
{
    this->CheckForQuit();
}

void GameState::Update(float dt)
{
    this->QuitCheck();
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;

    float mouseX;
    float mouseY;
    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;

    hpText.setString("HP: " + to_string(playerHp));
    goldText.setString("GOLD: " + to_string(playerGold));
    turnText.setString("WAVE: " + to_string(currentWave) + " / " + to_string(waves));

    spawnTimer += dt;

    if (spawnTimer >= spawnDelay && monsters.size() < monsterPerWave)
    {
        spawnTimer = 0.f;

        if (!pathPoints.empty())
        {
            monsters.emplace_back(pathPoints[0]);

        }
    }
    for (int i = monsters.size() - 1; i >= 0; i--)
    {
        monsters[i].Update(dt, pathPoints);

        if (monsters[i].reachedEnd)
        {
            playerHp -= monsters[i].mDamage;
            monsters.erase(monsters.begin() + i);
        }
    }

    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].IsMouseOver(mouseX, mouseY) && i != selectedTile && tiles[i].state ==  Tile::TileState::Placement) {
            tiles[i].shape.setFillColor(sf::Color::Cyan);
        }
        else if(i != selectedTile && tiles[i].state == Tile::TileState::Placement){
            tiles[i].shape.setFillColor(tiles[i].normalColor);
        }
        if (tiles[i].IsButtonClicked(mouseX, mouseY) && tiles[i].state == Tile::TileState::Placement && selectedTile != i) {
            selectedTile = i;
            isTileSelected = true;
            tiles[i].shape.setFillColor(sf::Color(156, 242, 116));
        }
        else if(tiles[i].IsButtonClicked(mouseX, mouseY) && selectedTile == i && tiles[i].state == Tile::TileState::Placement){
            tiles[i].shape.setFillColor(tiles[i].normalColor);
            isTileSelected = false;
            selectedTile = -1;
        }
    }
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].UpdateHover(mouseX, mouseY);
    }
    if (playerHp <= 0) {
        this->nextState = new MainMenuState(this->windowPtr);
        quit = true;
    }

}

void GameState::Render(sf::RenderWindow* windowPtr)
{
    for (auto& tile : tiles)
        tile.Draw(*windowPtr);
    for (auto& button : buttons)
        button.Draw(*windowPtr);
    for (auto& monster : monsters)
        monster.Draw(*windowPtr);

    windowPtr->draw(hpBox);
    windowPtr->draw(goldBox);
    windowPtr->draw(turnBox);

    windowPtr->draw(hpText);
    windowPtr->draw(goldText);
    windowPtr->draw(turnText);
}
