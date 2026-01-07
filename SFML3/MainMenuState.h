#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"
#include "Button.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class MainMenuState : public States
{
public:
    // --- Konstruktor i Destruktor ---
    MainMenuState(sf::RenderWindow* windowPtr);
    ~MainMenuState();

    // --- Implementacja metod wirtualnych i logika ---
    void EndState() override;
    void Update(float dt) override;
    void Render(sf::RenderWindow* windowPtr) override;

    // --- Zarz¹dzanie stanem menu ---
    void QuitCheck();
    void CopyMap(string source, string dest); // Pomocnicza funkcja do plików map

private:
    // --- Parametry ekranu ---
    float screenWidth;
    float screenHeight;

    // --- Zasoby i Typy ---
    sf::Font fontMainMenu;

    enum class MenuState {
        Main,
        LevelSelect,
        Options
    };
    MenuState menuState = MenuState::Main;

    // --- Przyciski: G³ówne Menu ---
    Button startBtn;
    Button optBtn;
    Button quitBtn;

    // --- Przyciski: Wybór Poziomu ---
    Button selectMenuLevelOne;
    Button selectMenuLevelTwo;
    Button selectMenuLevelThree;

    // --- Przyciski: Wybór Trudnoœci ---
    Button selectMenuEasy;
    Button selectMenuNormal;
    Button selectMenuHard;

    // --- Nawigacja ---
    Button backToMenu;
};