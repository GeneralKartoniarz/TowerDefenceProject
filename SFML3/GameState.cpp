#include "GameState.h"   
#include "States.h"           
#include "Tile.h"           
#include "Button.h"      
#include <iostream>   
#include <string>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
using namespace std;  
sf::Font fontGameState("comicFont.ttf");

GameState::GameState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
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
            tiles.emplace_back(position, tileSize);
        }
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
    for (auto& tile : tiles) {
        if (tile.IsMouseOver(mouseX, mouseY) && tile.shape.getFillColor() != sf::Color::White)
            tile.shape.setFillColor(sf::Color::Red);
        else if(tile.shape.getFillColor() != sf::Color::White)
            tile.shape.setFillColor(sf::Color::Blue);
        if(tile.IsButtonClicked(mouseX,mouseY))
            tile.shape.setFillColor(sf::Color::White);
    }
}

void GameState::Render(sf::RenderWindow* windowPtr)
{
    for (auto& tile : tiles)
        tile.Draw(*windowPtr);
}
