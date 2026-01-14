#include "MainMenuState.h"
#include "GameState.h"
#include "States.h"      
#include "Button.h"      
#include <iostream>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>

using namespace std;

// Zmienna globalna kontroluj¹ca trudnoœæ
int difficulty = 1;

// --- KONSTRUKTOR ---
MainMenuState::MainMenuState(sf::RenderWindow* windowPtr)
    : States(windowPtr),
    startBtn(fontMainMenu),
    quitBtn(fontMainMenu),
    optBtn(fontMainMenu),
    selectMenuEasy(fontMainMenu),
    selectMenuNormal(fontMainMenu),
    selectMenuHard(fontMainMenu),
    selectMenuLevelOne(fontMainMenu),
    selectMenuLevelTwo(fontMainMenu),
    selectMenuLevelThree(fontMainMenu),
    backToMenu(fontMainMenu),
    titleText(fontMainMenu)
{
    // £adowanie zasobów
    if (!fontMainMenu.openFromFile("comicFont.ttf")) {
        cout << "Font sie zepsul";
    }

    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;


    // Inicjalizacja: Menu G³ówne
    startBtn.text.setString("Start");
    startBtn.SetPosition(screenWidth / 2, screenHeight / 3);

    optBtn.text.setString("Options");
    optBtn.SetPosition(screenWidth / 2, screenHeight / 2);

    quitBtn.text.setString("Exit");
    quitBtn.SetPosition(screenWidth / 2, screenHeight - screenHeight / 3);

    titleText.setString("A.I FIGHTER - Freedom Keeper");
    titleText.setFillColor(sf::Color::White);
    titleText.setCharacterSize(60);
    titleText.setOrigin({ titleText.getLocalBounds().size.x/2, titleText.getLocalBounds().size.y/2});
    titleText.setPosition({ screenWidth / 2,screenHeight/2 - 330.f });

    // Inicjalizacja: Wybór poziomu trudnoœci
    selectMenuEasy.shape.setFillColor(sf::Color::Blue);
    selectMenuEasy.text.setString("Easy");
    selectMenuEasy.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.7);

    selectMenuNormal.shape.setFillColor(sf::Color::Blue);
    selectMenuNormal.text.setString("Medium");
    selectMenuNormal.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.5);

    selectMenuHard.shape.setFillColor(sf::Color::Blue);
    selectMenuHard.text.setString("Hard");
    selectMenuHard.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.3);

    // Inicjalizacja: Wybór konkretnego poziomu (Mapy)
    selectMenuLevelOne.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelOne.text.setString("1");
    selectMenuLevelOne.SetPosition(screenWidth - screenWidth * 0.7, screenHeight - screenHeight * 0.9);

    selectMenuLevelTwo.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelTwo.text.setString("2");
    selectMenuLevelTwo.SetPosition(screenWidth - screenWidth * 0.5, screenHeight - screenHeight * 0.9);

    selectMenuLevelThree.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelThree.text.setString("3");
    selectMenuLevelThree.SetPosition(screenWidth - screenWidth * 0.3, screenHeight - screenHeight * 0.9);

    // Inicjalizacja: Przycisk powrotu
    backToMenu.shape.setFillColor(sf::Color::Blue);
    backToMenu.text.setString("<-");
    backToMenu.SetPosition(backToMenu.shape.getSize().x, backToMenu.shape.getSize().y);
}

MainMenuState::~MainMenuState() {}

void MainMenuState::EndState()
{
    cout << "Wybrano poziom";
}

void MainMenuState::QuitCheck()
{
    this->CheckForQuit();
}

// --- AKTUALIZACJA LOGIKI ---
void MainMenuState::Update(float dt)
{
    this->QuitCheck();
    float mouseX = sf::Mouse::getPosition(*windowPtr).x;
    float mouseY = sf::Mouse::getPosition(*windowPtr).y;
    
    // Logika Menu G³ównego
    if (menuState == MenuState::Main) {
        startBtn.UpdateHover(mouseX, mouseY);
        if (startBtn.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::LevelSelect;
        }

        optBtn.UpdateHover(mouseX, mouseY);
        if (optBtn.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Options;
        }

        quitBtn.UpdateHover(mouseX, mouseY);
        if (quitBtn.IsButtonClicked(mouseX, mouseY)) {
            windowPtr->close();
        }
    }

    // Logika Wyboru Poziomu i Trudnoœci
    if (menuState == MenuState::LevelSelect) {
        // Obs³uga trudnoœci
        if (selectMenuEasy.IsButtonClicked(mouseX, mouseY)) {
            difficulty = 1;
            selectMenuEasy.shape.setFillColor(sf::Color::Red);
            selectMenuNormal.shape.setFillColor(sf::Color::Blue);
            selectMenuHard.shape.setFillColor(sf::Color::Blue);
        }
        if (selectMenuNormal.IsButtonClicked(mouseX, mouseY)) {
            difficulty = 2;
            selectMenuNormal.shape.setFillColor(sf::Color::Red);
            selectMenuEasy.shape.setFillColor(sf::Color::Blue);
            selectMenuHard.shape.setFillColor(sf::Color::Blue);
        }
        if (selectMenuHard.IsButtonClicked(mouseX, mouseY)) {
            difficulty = 3;
            selectMenuHard.shape.setFillColor(sf::Color::Red);
            selectMenuEasy.shape.setFillColor(sf::Color::Blue);
            selectMenuNormal.shape.setFillColor(sf::Color::Blue);
        }

        // Obs³uga wyboru mapy i przejœcie do GameState
        if (selectMenuLevelOne.IsButtonClicked(mouseX, mouseY)) {
            CopyMap("map_1.txt", "map.txt");
            nextState = new GameState(windowPtr, 1);
            quit = true;
        }
        if (selectMenuLevelTwo.IsButtonClicked(mouseX, mouseY)) {
            CopyMap("map_2.txt", "map.txt");
            nextState = new GameState(windowPtr, 2);
            quit = true;
        }
        if (selectMenuLevelThree.IsButtonClicked(mouseX, mouseY)) {
            CopyMap("map_3.txt", "map.txt");
            nextState = new GameState(windowPtr, 3);
            quit = true;
        }

        backToMenu.UpdateHover(mouseX, mouseY);
        if (backToMenu.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Main;
        }
    }

    // Logika Opcji
    if (menuState == MenuState::Options) {
        backToMenu.UpdateHover(mouseX, mouseY);
        if (backToMenu.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Main;
        }
    }
}

// --- RENDEROWANIE ---
void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    if (menuState == MenuState::Main) {
        startBtn.Draw(*windowPtr);
        quitBtn.Draw(*windowPtr);
        optBtn.Draw(*windowPtr);
        windowPtr->draw(titleText);
    }
    else if (menuState == MenuState::LevelSelect) {
        selectMenuEasy.Draw(*windowPtr);
        selectMenuNormal.Draw(*windowPtr);
        selectMenuHard.Draw(*windowPtr);

        selectMenuLevelOne.Draw(*windowPtr);
        selectMenuLevelTwo.Draw(*windowPtr);
        selectMenuLevelThree.Draw(*windowPtr);
        backToMenu.Draw(*windowPtr);
    }
    else if (menuState == MenuState::Options) {
        backToMenu.Draw(*windowPtr);
    }
}

// --- METODY POMOCNICZE ---
void MainMenuState::CopyMap(string source, string dest)
{
    ifstream sourceFile(source);
    ofstream destFile(dest, ios::trunc);
    destFile << sourceFile.rdbuf();
    sourceFile.close();
    destFile.close();
}