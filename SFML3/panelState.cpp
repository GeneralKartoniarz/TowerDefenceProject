#include "panelState.h"
#include <iostream>

using namespace std;

panelState::panelState(sf::RenderWindow* windowPtr,string message,States* next): States(windowPtr), text(font)
{
    nextState = next;

    if (!font.openFromFile("comicFont.ttf"))
        cout << "Nie zaladowano fontu\n";

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(64);
    text.setFillColor(sf::Color(255, 0, 0, 0));

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    text.setPosition({windowPtr->getSize().x / 2.f,windowPtr->getSize().y / 2.f});
}

void panelState::Update(float dt)
{
    switch (phase)
    {
    case Phase::FadeIn:
        alpha += 200.f * dt;
        if (alpha >= 255.f)
        {
            alpha = 255.f;
            phase = Phase::Hold;
        }
        break;

    case Phase::Hold:
        timer += dt;
        if (timer >= .5f)
            phase = Phase::FadeOut;
        break;

    case Phase::FadeOut:
        alpha -= 200.f * dt;
        if (alpha <= 0.f)
        {
            quit = true;
            return;
        }
        break;
    }

    text.setFillColor(sf::Color(255, 0, 0, alpha));
}

void panelState::Render(sf::RenderWindow* windowPtr)
{
    windowPtr->draw(text);
}

void panelState::EndState()
{
}
