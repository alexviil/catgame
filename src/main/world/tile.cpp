#include "tile.h"
#include "../../constants.h"

int tile::getX() const {
    return x;
}

void tile::setX(int xn) {
    tile::x = xn;
}

int tile::getY() const {
    return y;
}

void tile::setY(int yn) {
    tile::y = yn;
}

void tile::setTexture(sf::Texture *newTexture) {
    tile::texture = newTexture;
}

const sf::Sprite &tile::getSprite() const {
    return sprite;
}

void tile::setSprite(const sf::Sprite &newSprite) {
    tile::sprite = newSprite;
}

tile::tile(int x, int y, sf::Texture *texture) : x(x), y(y), texture(texture) {
    tile::sprite.setPosition(sf::Vector2f(x, y));
    tile::sprite.setTexture(*texture);
}