#include "GameState.h"   
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
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;  

GameState::GameState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
    
    if (!fontGameState.openFromFile("comicFont.ttf")) {
        cout << "Font sie zepsul";
    }
    else {
        fontGameState.openFromFile("comicFont.ttf");
    }
    srand(time(0));
    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;
    
    tiles.clear();
    tiles.reserve(columns * rows);
    
    float gridWidth = columns * tileSize + (columns - 1) * spacing;
    
    float gridHeight = rows * tileSize + (rows - 1) * spacing;
    
    sf::Vector2f offset((screenWidth - gridWidth) / 2.f + tileSize / 2.f, screenHeight - gridHeight + tileSize / 2.f-40);
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
       {
           sf::Vector2f position(offset.x + j * (tileSize + spacing), offset.y + i * (tileSize + spacing));
           tiles.emplace_back(position, tileSize, Tile::TileState::Placement);
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

        buttons[i].normalColor = sf::Color::Magenta;
        buttons[i].hoverColor = sf::Color(255, 200, 0);
        buttons[i].shape.setFillColor(buttons[i].normalColor);

        float x = startX + i * (buttonWidth + buttonSpacing);
        buttons[i].SetPosition(x, y);
    }



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
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].IsMouseOver(mouseX, mouseY) && i != selectedTile && tiles[i].state ==  Tile::TileState::Placement) {
            tiles[i].shape.setFillColor(sf::Color::Cyan);
        }
        else if(i != selectedTile && tiles[i].state == Tile::TileState::Placement){
            tiles[i].shape.setFillColor(sf::Color::Blue);
        }
        if (tiles[i].IsButtonClicked(mouseX, mouseY) && tiles[i].state == Tile::TileState::Placement && selectedTile != i) {
            selectedTile = i;
            isTileSelected = true;
            tiles[i].shape.setFillColor(sf::Color::Red);
        }
        else if(tiles[i].IsButtonClicked(mouseX, mouseY) && selectedTile == i && tiles[i].state == Tile::TileState::Placement){
            tiles[i].shape.setFillColor(sf::Color::Blue);
            isTileSelected = false;
            selectedTile = -1;
        }
    }
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].UpdateHover(mouseX, mouseY);
    }
}

void GameState::Render(sf::RenderWindow* windowPtr)
{
    for (auto& tile : tiles)
        tile.Draw(*windowPtr);
    for (auto& button : buttons)
        button.Draw(*windowPtr);
}
