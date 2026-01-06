#include "MainMenuState.h"
#include "States.h"      
#include "Button.h"      
#include <iostream>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

int level = 1;
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
    backToMenu(fontMainMenu)
{
  
    if (!fontMainMenu.openFromFile("comicFont.ttf")) {
        cout << "Font sie zepsul";
    }
    this->windowPtr = windowPtr;
    this->screenHeight = windowPtr->getSize().y;
    this->screenWidth = windowPtr->getSize().x;

    startBtn.text.setString("Start");
    startBtn.SetPosition(screenWidth / 2, screenHeight / 3);

    optBtn.text.setString("Options");
    optBtn.SetPosition(screenWidth / 2, screenHeight / 2);

    quitBtn.text.setString("Exit");
    quitBtn.SetPosition(screenWidth / 2, screenHeight - screenHeight / 3);

    selectMenuEasy.shape.setFillColor(sf::Color::Blue);
    selectMenuEasy.text.setString("Easy");
    selectMenuEasy.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.7);
    selectMenuNormal.shape.setFillColor(sf::Color::Blue);
    selectMenuNormal.text.setString("Medium");
    selectMenuNormal.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.5);
    selectMenuHard.shape.setFillColor(sf::Color::Blue);
    selectMenuHard.text.setString("Hard");
    selectMenuHard.SetPosition(screenWidth / 2, screenHeight - screenHeight * 0.3);

    selectMenuLevelOne.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelOne.text.setString("1");
    selectMenuLevelOne.SetPosition(screenWidth - screenWidth * 0.7, screenHeight - screenHeight * 0.9);
    selectMenuLevelTwo.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelTwo.text.setString("2");
    selectMenuLevelTwo.SetPosition(screenWidth - screenWidth * 0.5, screenHeight - screenHeight * 0.9);
    selectMenuLevelThree.shape.setFillColor(sf::Color::Blue);
    selectMenuLevelThree.text.setString("3");
    selectMenuLevelThree.SetPosition(screenWidth - screenWidth * 0.3, screenHeight - screenHeight * 0.9);

    backToMenu.shape.setFillColor(sf::Color::Blue);
    backToMenu.text.setString("<-");
    backToMenu.SetPosition(backToMenu.shape.getSize().x, backToMenu.shape.getSize().y);
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::EndState()
{
    cout << "Wybrano poziom";
}

void MainMenuState::QuitCheck()
{
    this->CheckForQuit();
}

void MainMenuState::Update(float dt)
{
    this->QuitCheck();
    float mouseX;
    float mouseY;

    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;

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
    if (menuState == MenuState::LevelSelect) {
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
        if (selectMenuLevelOne.IsButtonClicked(mouseX, mouseY)) {
            level = 1;
            this->quit = true;
        }

        if (selectMenuLevelTwo.IsButtonClicked(mouseX, mouseY)) {
            level = 2;
            this->quit = true;
        }

        if (selectMenuLevelThree.IsButtonClicked(mouseX, mouseY)) {
            level = 3;
            this->quit = true;
        }

        backToMenu.UpdateHover(mouseX, mouseY);
        if (backToMenu.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Main;
        }
    }


    if (menuState == MenuState::Options) {
        backToMenu.UpdateHover(mouseX, mouseY);
        if (backToMenu.IsButtonClicked(mouseX, mouseY)) {
            menuState = MenuState::Main;
        }
    }
}

void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    if (menuState == MenuState::Main) {
        startBtn.Draw(*windowPtr);
        quitBtn.Draw(*windowPtr);
        optBtn.Draw(*windowPtr);
    }
    if (menuState == MenuState::LevelSelect) {
        selectMenuEasy.Draw(*windowPtr);
        selectMenuNormal.Draw(*windowPtr);
        selectMenuHard.Draw(*windowPtr);

        selectMenuLevelOne.Draw(*windowPtr);
        selectMenuLevelTwo.Draw(*windowPtr);
        selectMenuLevelThree.Draw(*windowPtr);
        backToMenu.Draw(*windowPtr);
    }
    if (menuState == MenuState::Options) {
        backToMenu.Draw(*windowPtr);

    }

}
