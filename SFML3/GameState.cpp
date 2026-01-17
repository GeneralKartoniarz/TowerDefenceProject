#include "GameState.h"   
#include "panelState.h"   
#include "MainMenuState.h"   
#include "MusicManager.h"   
#include "States.h"           
#include "Tile.h"           
#include "Button.h"      
#include "Bullet.h"      
#include "Monster.h"      
#include "BasicMonster.h"      
#include "BasicTower.h"            
#include "LaserTower.h"
#include "MissleTower.h"
#include "EMPtower.h"
#include "Hackertower.h"
#include "FastMonster.h"      
#include "TankMonster.h"      
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
#include <memory>

using namespace std;

GameState::GameState(sf::RenderWindow* windowPtr, int difficulty)
    : States(windowPtr), hpText(fontGameState), goldText(fontGameState), turnText(fontGameState), pauseText(fontGameState), waveBtn(fontGameState), upgradeButton(fontGameState),upgradeText(fontGameState)
{
    musicManager.LoadMusic("game", "assets/music/game.mp3");
    musicManager.Play("game");
    // 1. Deserializacja mapy z pliku zewnêtrznego
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

    // 2. Inicjalizacja parametrów systemowych i zasobów tekstowych
    if (!fontGameState.openFromFile("comicFont.ttf")) {
        cout << "B³¹d ³adowania czcionki.";
    }
    srand(static_cast<unsigned>(time(0)));
    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;
    this->difficulty = difficulty;

    // Konfiguracja komunikatu pauzy
    pauseText.setFont(fontGameState);
    pauseText.setString("PAUZA");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::Red);
    pauseText.setOrigin({ pauseText.getLocalBounds().size.x / 2.f, pauseText.getLocalBounds().size.y / 2.f });
    pauseText.setPosition({ this->screenWidth / 2.f, this->screenHeight / 2.f });
    pauseBackground.setSize({ 1920, 1080 });
    pauseBackground.setFillColor(sf::Color(150, 0, 0, 100));
    // Inicjalizacja kontrolera fal (Wave Button)
    waveBtn.SetPosition(screenWidth - screenWidth / 11, screenHeight / 11);
    waveBtn.shape.setScale({ 0.5f, 1.f });
    waveBtn.normalColor = sf::Color(122, 122, 122);
    waveBtn.hoverColor = sf::Color(80, 80, 80);
    waveBtn.text.setCharacterSize(13.f);
    waveBtn.text.setString("START");
    waveBtn.CenterText();
    waveBtn.shape.setFillColor(waveBtn.normalColor);
    waveBtn.LoadTexture("assets/button/menu2.png");
    waveBtn.text.setFillColor(sf::Color::Red);

    upgradePanel.setSize({ 200.f, 100.f });
    upgradePanel.setFillColor(sf::Color(30, 30, 30, 220));
    upgradePanel.setOutlineThickness(2.f);
    upgradePanel.setOutlineColor(sf::Color::White);

    upgradeText.setFont(fontGameState);
    upgradeText.setCharacterSize(16);
    upgradeText.setFillColor(sf::Color::White);

    upgradeButton.text.setString("UPGRADE");
    upgradeButton.text.setCharacterSize(6);
    upgradeButton = Button(fontGameState);
    upgradeButton.text.setString("UPGRADE");
    upgradeButton.text.setCharacterSize(16);
    upgradeButton.text.setFillColor(sf::Color::White);
    upgradeButton.CenterText();
    upgradeButton.hoverColor = sf::Color(0, 0,0,0);
    upgradeButton.normalColor = sf::Color(0, 0,0,0);


    // 3. Generowanie siatki gry (Grid System)
    tiles.clear();
    tiles.reserve(columns * rows);
    bullets.clear();

    float gridWidth = columns * tileSize + (columns - 1) * spacing;
    float gridHeight = rows * tileSize + (rows - 1) * spacing;
    sf::Vector2f offset((screenWidth - gridWidth) / 2.f + tileSize / 2.f, screenHeight - gridHeight + tileSize / 2.f - 40);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int currentTile = i * columns + j;
            sf::Vector2f position(offset.x + j * (tileSize + spacing), offset.y + i * (tileSize + spacing));

            Tile::TileState state;
            char type = mapString[currentTile];

            // Mapowanie znaków z pliku na stany kafelków
            if (type == '1') state = Tile::TileState::Path;
            else if (type == '2') state = Tile::TileState::Locked;
            else state = Tile::TileState::Placement;

            tiles.emplace_back(position, tileSize, state);
            tiles.back().Refresh();
        }
    }

    // 4. Algorytm wyznaczania punktów nawigacyjnych (Waypoint Pathfinding)
    pathPoints.clear();
    int startIndex = -1;
    for (int i = 0; i < map.size(); i++) {
        if (map[i] == '1') {
            startIndex = i;
            break;
        }
    }

    if (startIndex != -1) {
        int current = startIndex;
        int previous = -1;
        bool endOfPath = false;

        while (!endOfPath) {
            pathPoints.push_back(tiles[current].shape.getPosition());

            bool foundNext = false;
            const int dirs[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

            for (auto& d : dirs) {
                int nx = (current % columns) + d[0];
                int ny = (current / columns) + d[1];
                int next = ny * columns + nx;
                if (nx >= 0 && nx < columns && ny >= 0 && ny < rows) {
                    if (map[next] == '1' && next != previous) {
                        previous = current;
                        current = next;
                        foundNext = true;
                        break;
                    }
                }
            }
            if (!foundNext) endOfPath = true;
        }
    }
    mapFile.close();
    // 5. Inicjalizacja interfejsu sklepu (Tower Shop)
    int buttonCount = 6;
    float buttonSpacing = 20.f;
    float topMargin = 15.f;
    towers.clear();
    buttons.clear();
    buttons.reserve(buttonCount);

    for (int i = 0; i < buttonCount; i++) buttons.emplace_back(fontGameState);

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
        buttons[i].SetPosition(startX + i * (buttonWidth + buttonSpacing), y);
        buttons[i].LoadTexture("assets/button/menu1.png");
    }

    // 6. Konfiguracja paneli statystyk (HUD Boxes)
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

    hpText.setCharacterSize(20.f);
    hpText.setPosition(hpBox.getPosition() + sf::Vector2f(8, 8));
    goldText.setCharacterSize(20.f);
    goldText.setPosition(goldBox.getPosition() + sf::Vector2f(8, 8));
    turnText.setCharacterSize(20.f);
    turnText.setPosition(turnBox.getPosition() + sf::Vector2f(8, 8));
}

GameState::~GameState() {}

void GameState::EndState() {}

void GameState::QuitCheck() { this->CheckForQuit(); }

void GameState::Update(float dt)
{
    // Obs³uga prze³¹cznika pauzy
    static bool pausePressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
    {
        if (!pausePressed)
        {
            isGamePaused = !isGamePaused;

            if (isGamePaused)
                musicManager.Pause();
            else
                musicManager.Resume();

            pausePressed = true;
        }
    }
    else
    {
        pausePressed = false;
    }
    if (isGamePaused)
        return;

    this->QuitCheck();

    float mouseX = sf::Mouse::getPosition(*windowPtr).x;
    float mouseY = sf::Mouse::getPosition(*windowPtr).y;

    // Odœwie¿anie danych w interfejsie u¿ytkownika
    hpText.setString("HP: " + to_string(playerHp));
    goldText.setString("GOLD: " + to_string(playerGold));
    turnText.setString("WAVE: " + to_string(currentWave) + " / " + to_string(waves));

    // Zarz¹dzanie przyciskiem startu fali
    waveBtn.UpdateHover(mouseX, mouseY);
    if (waveBtn.IsButtonClicked(mouseX, mouseY) && !waveActive)
    {
        waveActive = true;
        spawnTimer = 0.f;
        monstersSpawnedThisWave = 0;

    }

    // Generator przeciwników (Spawn Manager)
    if (waveActive)
    {
        spawnTimer += dt;
        if (spawnTimer >= spawnDelay && monstersSpawnedThisWave < monsterPerWave)
        {
            spawnTimer = 0.f;
            if (!pathPoints.empty())
            {
                int type = rand() % 3;
                if (type == 0) monsters.push_back(make_unique<BasicMonster>(pathPoints[0]));
                else if (type == 1) monsters.push_back(make_unique<FastMonster>(pathPoints[0]));
                else monsters.push_back(make_unique<TankMonster>(pathPoints[0]));

                monsters.back()->baseSpeed *= difficulty;
                monstersSpawnedThisWave++;
            }
        }
    }

    // Przetwarzanie stanów jednostek przeciwnika
    for (int i = monsters.size() - 1; i >= 0; i--)
    {
        monsters[i]->Update(dt, pathPoints);

        if (monsters[i]->reachedEnd)
        {
            playerHp -= monsters[i]->mDamage;
            monsters.erase(monsters.begin() + i);
        }
        else if (monsters[i]->isDead)
        {
            playerGold += monsters[i]->mGold;
            monsters.erase(monsters.begin() + i);
        }
    }

    // Logika zakoñczenia fali i skalowania trudnoœci
    if (waveActive && monstersSpawnedThisWave >= monsterPerWave && monsters.empty())
    {
        waveActive = false;
        playerGold += 500;
        monsterPerWave += (currentWave * difficulty);
        currentWave++;

    }

    // Interakcja z siatk¹ kafelków (Hover & Selection)
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].IsMouseOver(mouseX, mouseY) && i != selectedTile && tiles[i].state == Tile::TileState::Placement) {
            tiles[i].shape.setFillColor(sf::Color::Cyan);
        }
        else if (i != selectedTile && tiles[i].state == Tile::TileState::Placement) {
            tiles[i].shape.setFillColor(tiles[i].normalColor);
        }

        if (tiles[i].IsButtonClicked(mouseX, mouseY) && tiles[i].state == Tile::TileState::Placement) {
            if (selectedTile == i) {
                isTileSelected = false;
                selectedTile = -1;
            }
            else {
                selectedTile = i;
                isTileSelected = true;
                tiles[i].shape.setFillColor(sf::Color(156, 242, 116));
            }
        }
    }

    // Obs³uga zakupu wie¿ w sklepie
    buttons[0].text.setString("Normal\nTower");
    buttons[0].text.setCharacterSize(20);
    buttons[0].CenterText();

    buttons[1].text.setString("Laser\nTower");
    buttons[1].text.setCharacterSize(20);
    buttons[1].CenterText();

    buttons[2].text.setString("EMP\nTower");
    buttons[2].text.setCharacterSize(20);
    buttons[2].CenterText();

    buttons[3].text.setString("Hacker\nTower");
    buttons[3].text.setCharacterSize(20);
    buttons[3].CenterText();

    buttons[4].text.setString("Missle\nTower");
    buttons[4].text.setCharacterSize(20);
    buttons[4].CenterText();

    buttons[5].text.setString("Support\nNode");
    buttons[5].text.setCharacterSize(20);
    buttons[5].CenterText();

    for (auto& button : buttons) button.UpdateHover(mouseX, mouseY);

    if (isTileSelected) {
        if (buttons[0].IsButtonClicked(mouseX, mouseY) && playerGold >= BasicTower::COST) {
            towers.push_back(make_unique<BasicTower>(tiles[selectedTile].shape.getPosition()));
            playerGold -= BasicTower::COST;
            tiles[selectedTile].state = Tile::TileState::Locked;
            tiles[selectedTile].Refresh();
            isTileSelected = false;
        }
        else if (buttons[1].IsButtonClicked(mouseX, mouseY) && playerGold >= LaserTower::COST) {
            towers.push_back(make_unique<LaserTower>(tiles[selectedTile].shape.getPosition()));
            playerGold -= LaserTower::COST;
            tiles[selectedTile].state = Tile::TileState::Locked;
            tiles[selectedTile].Refresh();
            isTileSelected = false;
        }
        else if (buttons[2].IsButtonClicked(mouseX, mouseY) && playerGold >= EMPtower::COST) {
            towers.push_back(make_unique<EMPtower>(tiles[selectedTile].shape.getPosition()));
            playerGold -= EMPtower::COST;
            tiles[selectedTile].state = Tile::TileState::Locked;
            tiles[selectedTile].Refresh();
            isTileSelected = false;
        }
        else if (buttons[3].IsButtonClicked(mouseX, mouseY) && playerGold >= HackerTower::COST) {
            towers.push_back(make_unique<HackerTower>(tiles[selectedTile].shape.getPosition()));
            playerGold -= HackerTower::COST;
            tiles[selectedTile].state = Tile::TileState::Locked;
            tiles[selectedTile].Refresh();
            isTileSelected = false;
        }
        else if (buttons[4].IsButtonClicked(mouseX, mouseY) && playerGold >= MissleTower::COST) {
            towers.push_back(make_unique<MissleTower>(tiles[selectedTile].shape.getPosition()));
            playerGold -= MissleTower::COST;
            tiles[selectedTile].state = Tile::TileState::Locked;
            tiles[selectedTile].Refresh();
            isTileSelected = false;
        }
        else if (buttons[5].IsButtonClicked(mouseX, mouseY)) {
            cout << "ULEPSZ";
        }
    }

    // Aktualizacja mechaniki wie¿ i pocisków
    for (auto& tower : towers) tower->Update(dt, monsters, bullets);

    for (int i = bullets.size() - 1; i >= 0; i--) {
        bullets[i]->Update(dt);
        if (bullets[i]->isDead) bullets.erase(bullets.begin() + i);
    }

    bool clickedTower = false;

    for (auto& tower : towers)
    {
        if (tower->IsMouseOver(mouseX, mouseY) &&sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            selectedTowerPtr = tower.get();
            showUpgradePanel = true;
            clickedTower = true;
            selectedTowerPtr->isRangeShown = true;
            upgradePanel.setPosition(tower->tShape.getPosition() + sf::Vector2f(40, -40));
            upgradeText.setPosition(upgradePanel.getPosition() + sf::Vector2f(10, 10));
            upgradeButton.SetPosition(
                upgradePanel.getPosition().x + 100,
                upgradePanel.getPosition().y + 70
            );
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !clickedTower)
    {
        if (showUpgradePanel && !upgradePanel.getGlobalBounds().contains({ mouseX, mouseY }))
        {
            showUpgradePanel = false;
            selectedTowerPtr->isRangeShown = false;
            selectedTowerPtr = nullptr;
            
        }
    }
    if (showUpgradePanel && (selectedTowerPtr !=nullptr))
    {
        upgradeButton.UpdateHover(mouseX, mouseY);

        int cost = selectedTowerPtr->GetUpgradeCost();

        if (cost != -1)
            upgradeText.setString("Upgrade: " + to_string(cost));
        else
            upgradeText.setString("MAX LEVEL");

        if (upgradeButton.IsButtonClicked(mouseX, mouseY) &&
            cost != -1 &&
            playerGold >= cost)
        {
            playerGold -= cost;
            selectedTowerPtr->Upgrade();

            showUpgradePanel = false;
            selectedTowerPtr->isRangeShown = false;
            selectedTowerPtr = nullptr;
        }
    }

    // Weryfikacja warunku koñca gry
    if (playerHp <= 0) {
        this->nextState = new panelState(this->windowPtr,"HA HA HA HA HA HA",new MainMenuState(this->windowPtr));
        musicManager.Stop();
        quit = true;
    }
    if (currentWave > waves && monsters.empty()) {
        this->nextState = new panelState(this->windowPtr, "GRATULCAJE! WYGRANA! WYGRANA!", new MainMenuState(this->windowPtr));
        musicManager.Stop();
        quit = true;
    }
}

void GameState::Render(sf::RenderWindow* windowPtr)
{

    // Renderowanie elementów œwiata gry
    for (auto& tile : tiles) tile.Draw(*windowPtr);

    for (auto& button : buttons) button.Draw(*windowPtr);
    for (auto& monster : monsters) monster->Draw(*windowPtr);
    for (auto& tower : towers) tower->Draw(*windowPtr);
    for (auto& bullet : bullets) bullet->Draw(*windowPtr);

    // Renderowanie interfejsu HUD
    windowPtr->draw(hpBox);
    windowPtr->draw(goldBox);
    windowPtr->draw(turnBox);
    windowPtr->draw(hpText);
    windowPtr->draw(goldText);
    windowPtr->draw(turnText);

    if (!waveActive) waveBtn.Draw(*windowPtr);
    if (isGamePaused) {
        windowPtr->draw(pauseBackground);
        windowPtr->draw(pauseText);
    }
    if (showUpgradePanel && selectedTowerPtr)
    {
        windowPtr->draw(upgradePanel);
        windowPtr->draw(upgradeText);
        upgradeButton.Draw(*windowPtr);
    }

}