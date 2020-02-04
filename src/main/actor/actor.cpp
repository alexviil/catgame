#include "actor.h"

actor::actor(float x, float y, float speed, sf::Texture *currentTexture) : x(x), y(y), speed(speed),
                                                                       currentTexture(currentTexture) {
    actor::sprite.setPosition(sf::Vector2f(x, y));
    actor::sprite.setTexture(*currentTexture);
}

const sf::Sprite &actor::getSprite() const {
    return sprite;
}
