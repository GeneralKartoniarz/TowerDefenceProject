#pragma once
#include "States.h"
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
private:
};

