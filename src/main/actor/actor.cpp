#include <cmath>
#include "actor.h"
#include "../../constants.h"

actor::actor(float x, float y, float speed, const sf::Texture& currentTexture) : x(x), y(y), maxMomentum(speed),
                                                                           currentTexture(currentTexture) {
    actor::sprite.setPosition(sf::Vector2f(x, y));
    actor::sprite.setTexture(currentTexture);
    actor::sprite.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    animationFrames = currentTexture.getSize().y / TILE_HEIGHT;
}

void actor::animate() {
    //https://www.gamefromscratch.com/post/2015/10/26/SFML-CPP-Tutorial-Spritesheets-and-Animation.aspx
    float time = animationClock.getElapsedTime().asSeconds();

    switch (animatonState) {
        case idle:
            if (time >= 0.25f) {
                currentFrame++;
                if (currentFrame == animationFrames) {
                    currentFrame = 0;
                }
                if (spriteFlipped) {
                    actor::sprite.setTextureRect(sf::IntRect(TILE_WIDTH, TILE_HEIGHT * currentFrame, -TILE_WIDTH, TILE_HEIGHT));
                } else {
                    actor::sprite.setTextureRect(sf::IntRect(0, TILE_HEIGHT * currentFrame, TILE_WIDTH, TILE_HEIGHT));
                }
                animationClock.restart();
            }
            break;
        case walking:
            if (time >= 0.5f / sqrt(sqrt(xMomentum * xMomentum + yMomentum * yMomentum))) {
                currentFrame++;
                if (currentFrame == animationFrames) {
                    currentFrame = 0;
                }
                if (spriteFlipped) {
                    actor::sprite.setTextureRect(sf::IntRect(2 * TILE_WIDTH, TILE_HEIGHT * currentFrame, -TILE_WIDTH, TILE_HEIGHT));
                } else {
                    actor::sprite.setTextureRect(sf::IntRect(TILE_WIDTH, TILE_HEIGHT * currentFrame, TILE_WIDTH, TILE_HEIGHT));
                }
                animationClock.restart();
            }
            break;
    }
}

sf::Sprite &actor::getSprite() {
    return sprite;
}

float actor::getX() const {
    return x;
}

float actor::getY() const {
    return y;
}

float actor::getCollisionCentreX() {
    return x + TILE_WIDTH / 2.f;
}

float actor::getCollisionCentreY() {
    return y + TILE_HEIGHT / 2.f;
}

float actor::getCollisionBoxSideHalf() {
    return collisionBoxSideHalf;
}
