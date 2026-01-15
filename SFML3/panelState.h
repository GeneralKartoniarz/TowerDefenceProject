#pragma once
#include "States.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class panelState : public States
{
public:
    panelState(
        sf::RenderWindow* window,
        string message,
        States* nextState
    );

    void Update(float dt) override;
    void Render(sf::RenderWindow* window) override;
    void EndState() override;
private:
    sf::Font font;
    sf::Text text;

    float alpha = 0.f;
    float timer = 0.f;

    enum class Phase
    {
        FadeIn,
        Hold,
        FadeOut
    };

    Phase phase = Phase::FadeIn;
};
