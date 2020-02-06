#include "actor.h"

actor::actor(float x, float y, float speed, const sf::Texture& currentTexture) : x(x), y(y), maxMomentum(speed),
                                                                           currentTexture(currentTexture) {
    actor::sprite.setPosition(sf::Vector2f(x, y));
    actor::sprite.setTexture(currentTexture);
}

sf::Sprite &actor::getSprite() {
    return sprite;
}

float actor::getX() const {
    return x;
}

float actor::getXMomentum() const {
    return xMomentum;
}

float actor::getY() const {
    return y;
}

float actor::getYMomentum() const {
    return yMomentum;
}
