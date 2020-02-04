#ifndef CATGAME_TILE_H
#define CATGAME_TILE_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class tile {

private:
    int x;
    int y;
    sf::Texture* texture;
    sf::Sprite sprite;

public:
    tile(int x, int y, sf::Texture *texture);


    int getX() const;
    int getY() const;
    const sf::Sprite &getSprite() const;
    void setX(int x);
    void setY(int y);
    void setSprite(const sf::Sprite &newSprite);
    void setTexture(sf::Texture *newTexture);
};


#endif //CATGAME_TILE_H
