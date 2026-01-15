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

// Globalny modyfikator wp³ywaj¹cy na balans gry w GameState
int difficulty = 1;

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
    // £adowanie zasobów typograficznych
    if (!fontMainMenu.openFromFile("comicFont.ttf")) {
        cout << "B³¹d krytyczny: Nie odnaleziono pliku czcionki.";
    }

    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;

    // --- Konfiguracja interfejsu: Menu G³ówne ---
    startBtn.text.setString("Start");
    startBtn.SetPosition(screenWidth / 2, screenHeight / 3);

    optBtn.text.setString("Options");
    optBtn.SetPosition(screenWidth / 2, screenHeight / 2);

    quitBtn.text.setString("Exit");
    quitBtn.SetPosition(screenWidth / 2, screenHeight - screenHeight / 3);

    // Parametry wizualne tytu³u gry
    titleText.setString("A.I FIGHTER - Freedom Keeper");
    titleText.setFillColor(sf::Color::White);
    titleText.setCharacterSize(60);
    titleText.setOrigin({ titleText.getLocalBounds().size.x / 2, titleText.getLocalBounds().size.y / 2 });
    titleText.setPosition({ screenWidth / 2, screenHeight / 2 - 330.f });

    // --- Konfiguracja interfejsu: Poziomy Trudnoœci ---
    selectMenuEasy.shape.setFillColor(sf::Color::Blue);
    selectMenuEasy.text.setString("Easy");
    selectMenuEasy.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.7);

    selectMenuNormal.shape.setFillColor(sf::Color::Blue);
    selectMenuNormal.text.setString("Medium");
    selectMenuNormal.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.5);

    selectMenuHard.shape.setFillColor(sf::Color::Blue);
    selectMenuHard.text.setString("Hard");
    selectMenuHard.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.3);

    // --- Konfiguracja interfejsu: Wybór Map ---
    selectMenuLevelOne.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelOne.text.setString("1");
    selectMenuLevelOne.SetPosition(screenWidth - screenWidth * 0.7, screenHeight - screenHeight * 0.9);

    selectMenuLevelTwo.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelTwo.text.setString("2");
    selectMenuLevelTwo.SetPosition(screenWidth - screenWidth * 0.5, screenHeight - screenHeight * 0.9);

    selectMenuLevelThree.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelThree.text.setString("3");
    selectMenuLevelThree.SetPosition(screenWidth - screenWidth * 0.3, screenHeight - screenHeight * 0.9);

    // Konfiguracja przycisku powrotu do wy¿szego poziomu menu
    backToMenu.shape.setFillColor(sf::Color::Blue);
    backToMenu.text.setString("<-");
    backToMenu.SetPosition(backToMenu.shape.getSize().x, backToMenu.shape.getSize().y);
}

MainMenuState::~MainMenuState() {}

void MainMenuState::EndState()
{
    cout << "Zamykanie menu g³ównego...";
}

void MainMenuState::QuitCheck()
{
    this->CheckForQuit();
}

void MainMenuState::Update(float dt)
{
    this->QuitCheck();
    float mouseX = sf::Mouse::getPosition(*windowPtr).x;
    float mouseY = sf::Mouse::getPosition(*windowPtr).y;

    // Obs³uga logiki warstwowej menu (Finite State Machine wewn¹trz Menu)
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
    else if (menuState == MenuState::LevelSelect) {
        // Logika wyboru trudnoœci - zmiana parametrów i wizualnego stanu przycisków
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

        // Procedura uruchamiania gry: wybór mapy -> nadpisanie pliku roboczego -> zmiana stanu
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
    else if (menuState == MenuState::Options) {
        backToMenu.UpdateHover(mouseX, mouseY);
        if (backToMenu.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Main;
        }
    }
}

void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    // Renderowanie warstwowe zale¿ne od aktualnego podstanu menu
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

void MainMenuState::CopyMap(string source, string dest)
{
    // Fizyczne kopiowanie danych mapy ze Ÿród³a do pliku tymczasowego wykorzystywanego przez silnik
    ifstream sourceFile(source);
    ofstream destFile(dest, ios::trunc); // Flaga trunc zapewnia nadpisanie pliku
    destFile << sourceFile.rdbuf();
    sourceFile.close();
    destFile.close();
}