#pragma once
#include <SFML/Graphics.hpp>
#include "States.h"
#include "Button.h"
#include <string>
#include<iostream>
#include<fstream>
using namespace std;
class MainMenuState :
    public States
{
public:
    MainMenuState(sf::RenderWindow* windowPtr);
    ~MainMenuState();
    void EndState();
    void QuitCheck();
    void Update(float dt);
    void Render(sf::RenderWindow* windowPtr);
    void CopyMap(string source, string dest);
   
private:
    float screenWidth;
    float screenHeight;

    sf::Font fontMainMenu;
    Button startBtn;
    Button quitBtn;
    Button optBtn;

    Button selectMenuEasy;
    Button selectMenuNormal;
    Button selectMenuHard;

    Button selectMenuLevelOne;
    Button selectMenuLevelTwo;
    Button selectMenuLevelThree;

    Button backToMenu;

    enum class MenuState {
        Main,        
        LevelSelect, 
        Options      
    };
    MenuState menuState = MenuState::Main;
};

