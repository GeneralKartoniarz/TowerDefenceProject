#pragma once

#include "States.h"
#include "Button.h"
#include "Tile.h"
#include "Tower.h"
#include "Monster.h"

#include <vector>
#include <memory>
using namespace std;

class GameState : public States
{
public:
    // --- Konstruktor i Destruktor ---
    GameState(sf::RenderWindow* windowPtr, int difficulty);
    ~GameState();

    // --- Ustawienia Ekranu i Mapy ---
    float screenWidth;
    float screenHeight;
    int tileSize = 96;
    int columns = 19;
    int rows = 9;
    int spacing = 0;

    // --- Statystyki Gracza i Rozgrywki ---
    int difficulty;
    int playerGold = 2000;
    int playerHp = 200;
    int currentWave = 1;
    int waves = 50;

    // --- Logika Wyboru i Spawnowania ---
    int selectedTile;
    int selectedTower;
    bool isTileSelected = false;
    int monsterPerWave = 20;
    int monstersSpawnedThisWave = 0;
    float spawnTimer = 0.f;
    float spawnDelay = .2f;

    // --- Kontenery Danych ---
    vector<Tile> tiles;             // Kafle mapy
    vector<Button> buttons;         // Przyciski interfejsu
    vector<unique_ptr<Monster>> monsters; // Aktywne potwory
    vector<Tower> towers;           // Postawione wie¿e
    vector<int> map;                // Dane surowe mapy
    vector<sf::Vector2f> pathPoints; // Punkty œcie¿ki dla potworów

    // --- Zasoby i Elementy UI ---
    sf::Font fontGameState;

    sf::RectangleShape hpBox;
    sf::RectangleShape goldBox;
    sf::RectangleShape turnBox;

    sf::Text hpText;
    sf::Text goldText;
    sf::Text turnText;

    // --- Metody G³ówne ---
    void EndState() override;
    void QuitCheck();
    void Update(float dt) override;
    void Render(sf::RenderWindow* windowPtr) override;
private:
    // Sekcja prywatna (opcjonalnie do dodania metody pomocnicze, np. LoadMap)
};