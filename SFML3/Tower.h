#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Bullet.h"

using namespace std;

// Forward declaration klasy Monster w celu unikniêcia cyklicznych zale¿noœci
class Monster;

/**
 * @class Tower
 *  Abstrakcyjna klasa bazowa (interfejs) dla wszystkich typów jednostek obronnych.
 * * Definiuje wspólny interfejs oraz podstawowe atrybuty wymagane do funkcjonowania
 * dowolnej wie¿y w systemie gry.
 */
class Tower
{
public:
    // Wirtualny destruktor gwarantuje poprawne czyszczenie pamiêci klas pochodnych
    virtual ~Tower() = default;

    // --- Metody czysto wirtualne (Pure Virtual Functions) ---

    /**
     * @brief Aktualizuje logikê wie¿y (wykrywanie celów, strzelanie).
     * Musi zostaæ nadpisana przez konkretne klasy wie¿.
     */
    virtual void Update(float dt, vector<unique_ptr<Monster>>& monsters, vector<unique_ptr<Bullet>>& bullets) = 0;

    /**
     * @brief Renderuje obiekt wie¿y na ekranie.
     */
    virtual void Draw(sf::RenderWindow& window) = 0;

    // --- Metody pomocnicze ---

    /**
     * @brief £aduje teksturê i przypisuje j¹ do tShape.
     * @param path Œcie¿ka do pliku graficznego.
     */
    virtual void LoadTexture(const string& path);

    virtual void RotateToEnemy(Monster* target);

    // Reprezentacja wizualna wie¿y na siatce gry
    sf::RectangleShape tShape;
    int level = 1;
    int maxLevel = 4;

    int upgradeCost =100;

    bool isSelected = false;
    bool isRangeShown = false;

    sf::SoundBuffer buffer;
    sf::Sound sound;

    virtual void Upgrade();

    virtual int GetUpgradeCost();
    virtual bool IsMouseOver(float mouseX, float mouseY);
protected:
    // --- Atrybuty chronione (dostêpne dla klas pochodnych) ---

    int tCost;              // Koszt zakupu jednostki w z³ocie
    float tAttack;          // Wartoœæ zadawanych obra¿eñ
    float tRange;           // Promieñ skutecznego ra¿enia celów
    float attackCooldown;   // Minimalny odstêp czasu miêdzy kolejnymi strza³ami
    float attackTimer;      // Zegar monitoruj¹cy gotowoœæ wie¿y do ataku
    std::string tName;      // Unikalna nazwa identyfikacyjna typu wie¿y

    sf::Texture texture;    // Zasób graficzny przechowywany w pamiêci VRAM
};