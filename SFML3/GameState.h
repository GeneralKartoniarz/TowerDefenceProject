#pragma once
#include "States.h"
class GameState :
    public States
{
public:
    GameState(sf::RenderWindow* windowPtr);
    ~GameState();

    void EndState();
    void QuitCheck();
    void Update();
    void Render(sf::RenderWindow* windowPtr);
private:

};

