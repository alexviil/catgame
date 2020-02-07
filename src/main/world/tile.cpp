#include "tile.h"
#include "../../constants.h"

const sf::Sprite &tile::getSprite() const {
    return sprite;
}

tile::tile(int x, int y, const sf::Texture &texture, int frame, tile::tileState state) : x(x), y(y) {
    tile::state = state;
    tile::sprite.setPosition(sf::Vector2f(x, y));
    tile::sprite.setTexture(texture);
    tile::sprite.setTextureRect(sf::IntRect(0, frame * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
}

tile::tileState tile::getState() const {
    return state;
}

int tile::getDecelerationCoefficient() const {
    return decelerationCoefficient;
}

void tile::setDecelerationCoefficient(int decelerationCoefficient) {
    tile::decelerationCoefficient = decelerationCoefficient;
}

int tile::getX() const {
    return x;
}

int tile::getY() const {
    return y;
}
