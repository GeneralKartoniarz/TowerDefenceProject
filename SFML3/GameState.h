#pragma once

#include "States.h"
#include "Button.h"
#include "Tile.h"
#include "Tower.h"
#include "Monster.h"
#include "Bullet.h"
#include <vector>
#include <memory>

using namespace std;

/**
 * class GameState
 * G³ówny stan rozgrywki zarz¹dzaj¹cy logik¹ mapy, jednostek oraz interfejsu HUD.
 */
class GameState : public States
{
public:
    // Inicjalizuje sesjê gry z uwzglêdnieniem wybranego poziomu trudnoœci
    GameState(sf::RenderWindow* windowPtr, int difficulty);
    ~GameState();

    // --- Parametry geometryczne œwiata gry ---
    float screenWidth;
    float screenHeight;
    int tileSize = 96;          // Bazowy rozmiar pojedynczego kafelka siatki
    int columns = 19;           // Liczba kolumn w macierzy mapy
    int rows = 9;               // Liczba wierszy w macierzy mapy
    int spacing = 0;            // Odstêp miêdzy kafelkami (gaps)

    // --- Ekonomia i status sesji ---
    int difficulty;             // Mno¿nik trudnoœci wp³ywaj¹cy na statystyki wrogów
    int playerGold = 2000;      // Dostêpne fundusze na zakup wie¿
    int playerHp = 200;         // Punkty ¿ycia bazy gracza
    int currentWave = 1;        // Numer bie¿¹cej fali przeciwników
    int waves = 3;             // Maksymalna liczba fal w scenariuszu

    // --- Zarz¹dzanie logik¹ fali i interakcji ---
    int selectedTile;           // Indeks aktualnie podœwietlonego kafelka
    int selectedTower;          // Typ wybranej wie¿y ze sklepu
    bool isTileSelected = false;
    bool isGamePaused = false;
    bool waveActive = false;    // Flaga okreœlaj¹ca, czy trwa faza walki
    int monsterPerWave = 20;    // Bazowa liczba wrogów do zespawnowania
    int monstersSpawnedThisWave = 0;
    float spawnTimer = 0.f;     // Licznik czasu miêdzy spawnami
    float spawnDelay = .2f;     // Interwa³ czasowy pojawiania siê wrogów

    // --- Kontenery obiektów i dane mapy ---
    vector<Tile> tiles;                         // Fizyczna reprezentacja pod³o¿a
    vector<Button> buttons;                     // Elementy interfejsu zakupów (UI Shop)
    vector<unique_ptr<Monster>> monsters;       // Kolekcja aktywnych przeciwników
    vector<unique_ptr<Tower>> towers;           // Instancje postawionych jednostek obronnych
    vector<int> map;                            // Matryca typów terenu odczytana z pliku
    vector<sf::Vector2f> pathPoints;            // Wspó³rzêdne waypointów dla ruchu AI
    vector<unique_ptr<Bullet>> bullets;         // Kolekcja pocisków w locie

    // --- System prezentacji i UI (HUD) ---
    sf::Font fontGameState;

    sf::RectangleShape hpBox;                   // T³o wskaŸnika zdrowia
    sf::RectangleShape goldBox;                 // T³o wskaŸnika funduszy
    sf::RectangleShape turnBox;                 // T³o wskaŸnika fali
    sf::RectangleShape pauseBackground;         // T³o pauzy

    sf::Text hpText;                            // Tekstowa reprezentacja punktów ¿ycia
    sf::Text goldText;                          // Tekstowa reprezentacja z³ota
    sf::Text turnText;                          // Tekstowa reprezentacja numeru fali
    sf::Text pauseText;                         // Komunikat wyœwietlany podczas pauzy

    Button waveBtn;                             // Przycisk wyzwalaj¹cy kolejn¹ falê

    // --- Cykl ¿ycia stanu ---
    void EndState() override;                   // Obs³uga czyszczenia stanu przed usuniêciem
    void QuitCheck();                           // Weryfikacja ¿¹dania zamkniêcia gry
    void Update(float dt) override;             // Aktualizacja logiki klatka po klatce
    void Render(sf::RenderWindow* windowPtr) override; // Renderowanie warstwowe grafiki

private:
    // Tu mo¿na przenieœæ metody takie jak LoadMap() lub ResetWave()
};