#include "MainMenuState.h"
#include "States.h"      
#include "Button.h"      
#include <iostream>   
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;






sf::Font fontMainMenu("comicFont.ttf");


Button startBtn(fontMainMenu);
Button quitBtn(fontMainMenu);
Button optBtn(fontMainMenu);

Button selectMenuEasy(fontMainMenu);
Button selectMenuNormal(fontMainMenu);
Button selectMenuHard(fontMainMenu);

Button selectMenuLevelOne(fontMainMenu);
Button selectMenuLevelTwo(fontMainMenu);
Button selectMenuLevelThree(fontMainMenu);

Button backToMenu(fontMainMenu);

bool levelSelectionOn = false;
bool optionSelectionOn = false;


// Konstruktor MainMenuState
//Kod umieszczony poni¿ej wykona siê RAZ
MainMenuState::MainMenuState(sf::RenderWindow* windowPtr)
    : States(windowPtr)
{
    this->windowPtr = windowPtr;
    float screenWidth;
    float screenHeight;

    screenHeight = windowPtr->getSize().y;
    screenWidth = windowPtr->getSize().x;

    //Menu startowe
    startBtn.text.setString("Start");
    startBtn.SetPosition(screenWidth / 2, screenHeight / 3);

    optBtn.text.setString("Options");
    optBtn.SetPosition(screenWidth / 2, screenHeight / 2);

    quitBtn.text.setString("Exit");
    quitBtn.SetPosition(screenWidth / 2, screenHeight - screenHeight / 3);

    //Wybór poziomów
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

// Destruktor GameState
MainMenuState::~MainMenuState() {

}
// Funkcja wywo³ywana przy koñczeniu stanu
void MainMenuState::EndState()
{

}

// Sprawdza, czy stan powinien zostaæ zakoñczony
void MainMenuState::QuitCheck()
{
    this->CheckForQuit();
}

// G³ówna funkcja logiki stanu gry
// dt = delta time (czas jednej klatki)
//Kod w tej funkcji wykona siê CO KLATKE
void MainMenuState::Update(float dt)
{
    this->QuitCheck();

    float screenWidth;
    float screenHeight;

    screenHeight = windowPtr->getSize().y;
    screenWidth = windowPtr->getSize().x;

    float mouseX;
    float mouseY;

    mouseX = sf::Mouse::getPosition(*windowPtr).x;
    mouseY = sf::Mouse::getPosition(*windowPtr).y;
    //Przycisk Start
    if (startBtn.IsMouseOver(mouseX, mouseY))
        startBtn.shape.setFillColor(sf::Color::Red);
    else
        startBtn.shape.setFillColor(sf::Color::Magenta);
    if (startBtn.IsButtonClicked(mouseX, mouseY)) {
        levelSelectionOn = true;
    }
    //Przycisk opcji
    if (optBtn.IsMouseOver(mouseX, mouseY))
        optBtn.shape.setFillColor(sf::Color::Red);
    else
        optBtn.shape.setFillColor(sf::Color::Magenta);
    if (optBtn.IsButtonClicked(mouseX, mouseY)) {
        optionSelectionOn = true;
    }

    //Przycisk Wyjœcia
    if (quitBtn.IsMouseOver(mouseX, mouseY))
        quitBtn.shape.setFillColor(sf::Color::Red);
    else
        quitBtn.shape.setFillColor(sf::Color::Magenta);
    if (quitBtn.IsButtonClicked(mouseX,mouseY)) {
        windowPtr->close();
    }

    //Wybór poziomów
    if (levelSelectionOn) {

    }


}

// Funkcja renderuj¹ca stan gry
//W tej funkcji jedynie RENDERUJEMY!!
void MainMenuState::Render(sf::RenderWindow* windowPtr)
{
    if (!levelSelectionOn && !optionSelectionOn) {
        startBtn.Draw(*windowPtr);
        quitBtn.Draw(*windowPtr);
        optBtn.Draw(*windowPtr);
    }
    if (levelSelectionOn) {
        selectMenuEasy.Draw(*windowPtr);
        selectMenuNormal.Draw(*windowPtr);
        selectMenuHard.Draw(*windowPtr);

        selectMenuLevelOne.Draw(*windowPtr);
        selectMenuLevelTwo.Draw(*windowPtr);
        selectMenuLevelThree.Draw(*windowPtr);
    
        backToMenu.Draw(*windowPtr);
    }

}
