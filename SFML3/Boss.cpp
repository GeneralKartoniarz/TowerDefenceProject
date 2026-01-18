#include "Boss.h"
Boss::Boss(sf::Vector2f startPos): Monster(startPos)
{
    // Statystyki wytrzyma³oœciowe (3x wy¿sze HP ni¿ BasicMonster)
    mMaxHP = 12000.f;
    mHP = mMaxHP;
    shape.setSize({ 100.f, 100.f });
    shape.setOrigin(shape.getSize() / 2.f); // Centrowanie œrodka ciê¿koœci dla obrotów i kolizji
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);
    hpBarBackground.setSize({ 100.f, 6.f });
    hpBarBackground.setFillColor(sf::Color(50, 50, 50));
    hpBarBackground.setOrigin({ hpBarBackground.getSize().x / 2.f, 0.f });

    // Dynamiczne wype³nienie paska
    hpBarFill.setSize({ 100.f, 6.f });
    hpBarFill.setFillColor(sf::Color::Green);
    hpBarFill.setOrigin({ hpBarFill.getSize().x / 2.f, 0.f });
    // Statystyki ataku i nagrody
    mDamage = 1500;        // Znaczne obra¿enia zadawane bazie gracza po dotarciu do koñca
    mGold = 25;          // Wysoka nagroda za eliminacjê ze wzglêdu na trudnoœæ pokonania

    // Kinematyka jednostki
    mSpeed = 100.f;       // Niska prêdkoœæ wymuszaj¹ca d³u¿sz¹ ekspozycjê na ogieñ wie¿
    baseSpeed = mSpeed;

    // Reprezentacja wizualna (kolor stalowy/niebieski sugeruj¹cy opancerzenie)
    normalColor = sf::Color(100, 150, 200);
    shape.setSize({ 100.f, 100.f });
    shape.setOrigin(shape.getSize() / 2.f); // Centrowanie œrodka ciê¿koœci dla obrotów i kolizji
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startPos);
    hpBarBackground.setSize({ 100.f, 6.f });
    hpBarBackground.setFillColor(sf::Color(50, 50, 50));
    hpBarBackground.setOrigin({ hpBarBackground.getSize().x / 2.f, 13.f });

    // Dynamiczne wype³nienie paska
    hpBarFill.setSize({ 100.f, 6.f });
    hpBarFill.setFillColor(sf::Color::Green);
    hpBarFill.setOrigin({ hpBarFill.getSize().x / 2.f, 13.f });
}
void Boss::ChangeHpBar() {
    // Obliczanie wspó³czynnika wype³nienia (0.0 do 1.0)
    float hpPercent = mHP / mMaxHP;
    if (hpPercent < 0) hpPercent = 0;

    // Aktualizacja szerokoœci zielonego wype³nienia
    hpBarFill.setSize({ 100.f * hpPercent, 6.f });

    // Synchronizacja pozycji HUD z pozycj¹ obiektu (offset pionowy -40px)
    sf::Vector2f pos = shape.getPosition();
    hpBarBackground.setPosition({ pos.x, pos.y - 40.f });
    hpBarFill.setPosition({ pos.x, pos.y - 40.f });
}