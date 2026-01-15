#include "Tower.h"
#include "Monster.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

/**
 * @brief Implementacja ³adowania zasobów graficznych dla bazy wie¿y.
 * * Metoda zarz¹dza cyklem ¿ycia tekstury. Nale¿y pamiêtaæ, ¿e sf::RectangleShape
 * przechowuje jedynie wskaŸnik do tekstury, dlatego obiekt sf::Texture musi
 * istnieæ tak d³ugo, jak d³ugo wie¿a jest renderowana.
 */
void Tower::LoadTexture(const string& path)
{
    // Próba wczytania pliku graficznego z dysku do pamiêci RAM/VRAM
    if (!texture.loadFromFile(path))
    {
        // Obs³uga b³êdów w przypadku braku pliku lub nieobs³ugiwanego formatu
        cout << "B³¹d krytyczny: Nie za³adowano tekstury z lokalizacji: " << path << endl;
    }

    // Mapowanie tekstury na kszta³t geometryczny wie¿y
    // U¿ycie adresu (&texture) zapewnia, ¿e Shape korzysta z wczytanych danych
    tShape.setTexture(&texture);
}

void Tower::RotateToEnemy(Monster* target)
{
    sf::Vector2f dir = this->tShape.getPosition() - target->shape.getPosition();
    float angleRadian = atan2(dir.y, dir.x);
    float angleDeg = angleRadian * 180 / 3.141592f;
    this->tShape.setRotation(sf::degrees(angleDeg-90));
}
