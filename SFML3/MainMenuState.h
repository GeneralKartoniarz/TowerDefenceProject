#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"
#include "Button.h"
#include "MusicManager.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * class MainMenuState
 * Stan obs³uguj¹cy menu g³ówne, nawigacjê miêdzy poziomami oraz wybór trudnoœci.
 */
class MainMenuState : public States
{
public:
    // Inicjalizuje widok menu, ³aduje czcionki i konfiguruje uk³ad przycisków
    MainMenuState(sf::RenderWindow* windowPtr, bool isMuted);
    ~MainMenuState();

    // Metody cyklu ¿ycia stanu gry
    void EndState() override;
    void Update(float dt) override;
    void Render(sf::RenderWindow* windowPtr) override;

    // Funkcje steruj¹ce przep³ywem aplikacji
    void QuitCheck();

    // Zarz¹dza plikami mapy przed przejœciem do GameState
    void CopyMap(string source, string dest);

private:
    // Wymiary okna pobierane dynamicznie przy inicjalizacji
    float screenWidth;
    float screenHeight;

    // Zasoby typograficzne interfejsu
    sf::Font fontMainMenu;

    // Definicja wewnêtrznych warstw widoku menu (Podmenu)
    enum class MenuState {
        Main,           // Ekran startowy
        LevelSelect,    // Wybór mapy
        Options         // Ustawienia (wybór trudnoœci)
    };
    MenuState menuState = MenuState::Main;

    // Elementy interfejsu: Widok g³ówny
    Button startBtn;
    Button optBtn;
    Button quitBtn;

    // Elementy interfejsu: Selektor map (Level Design)
    Button selectMenuLevelOne;
    Button selectMenuLevelTwo;
    Button selectMenuLevelThree;

    // Elementy interfejsu: Parametry rozgrywki (Difficulty Scaling)
    Button selectMenuEasy;
    Button selectMenuNormal;
    Button selectMenuHard;

    Button muteMusic;
    Button muteSfx;

    // Przycisk nawigacji powrotnej
    Button backToMenu;

    bool isMuted = false;
    bool isSfxMuted = false;
    // Statyczne elementy tekstowe (np. logo/tytu³ gry)
    sf::Text titleText;

    //Muzyka
    MusicManager musicManager;
};