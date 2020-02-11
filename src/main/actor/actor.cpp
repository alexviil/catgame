#include <cmath>
#include <iostream>
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

void actor::momentumDecay(float time, bool moveUp, bool moveRight, bool moveDown, bool moveLeft) {
    if (!moveUp && !moveDown) {
        yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
    }
    if (!moveLeft && !moveRight) {
        xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
    }
}

void actor::move(bool moveUp, bool moveRight, bool moveDown, bool moveLeft, world& gameWorld) {
    float time = movementClock.restart().asSeconds();

    if (moveUp || moveRight || moveLeft || moveDown) {
        actor::animatonState = walking;
        if (moveUp && yMomentum >= -maxMomentum) {
            yMomentum -= time * acceleration * (moveLeft || moveRight ? 0.86603f : 1.f);
        } else if (moveDown && yMomentum <= maxMomentum) {
            yMomentum += time * acceleration * (moveLeft || moveRight ? 0.86603f : 1.f);
        } else {
            momentumDecay(time, moveUp, moveRight, moveDown, moveLeft);
        }
        if (moveLeft && xMomentum >= -maxMomentum) {
            flipSprite(true, moveLeft);
            xMomentum -= time * acceleration * (moveUp || moveDown ? 0.86603f : 1.f);
        } else if (moveRight && xMomentum <= maxMomentum) {
            flipSprite(false, moveLeft);
            xMomentum += time * acceleration * (moveUp || moveDown ? 0.86603f : 1.f);
        } else {
            momentumDecay(time, moveUp, moveRight, moveDown, moveLeft);
        }

        if (std::abs(xMomentum) > 0.86603f * maxMomentum && std::abs(yMomentum) > 0.86603f * maxMomentum) {
            xMomentum = 0.86603f * maxMomentum * (float(xMomentum > 0) - float(xMomentum < 0));
            yMomentum = 0.86603f * maxMomentum * (float(yMomentum > 0) - float(yMomentum < 0));
        }
    } else {
        actor::animatonState = idle;
        momentumDecay(time, moveUp, moveRight, moveDown, moveLeft);
    }

    std::vector<tile*> nextTiles = gameWorld.getTilesByCoordsSquare(getCollisionCentreX() + xMomentum,
                                                                    getCollisionCentreY() + yMomentum, getCollisionBoxSideHalf());
    for (int i = 0; i < nextTiles.capacity(); ++i) {
        tile* tile_p = nextTiles[i];
        switch (tile_p->getState()) {
            case tile::blocked:
                if ((getCollisionCentreY() + getCollisionBoxSideHalf() < float(tile_p->getY()) + TILE_HEIGHT &&
                     getCollisionCentreY() + getCollisionBoxSideHalf() > float(tile_p->getY()))
                    || (getCollisionCentreY() - getCollisionBoxSideHalf() < float(tile_p->getY()) + TILE_HEIGHT &&
                        getCollisionCentreY() - getCollisionBoxSideHalf() > float(tile_p->getY()))) {
                    if (getCollisionCentreX() - getCollisionBoxSideHalf() > float(tile_p->getCentreX())) {
                        xMomentum = 0.1f;
                    } else if (getCollisionCentreX() + getCollisionBoxSideHalf() < float(tile_p->getCentreX())) {
                        xMomentum = -0.1f;
                    }
                }

                if ((getCollisionCentreX() + getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                     getCollisionCentreX() + getCollisionBoxSideHalf() > float(tile_p->getX()))
                    || (getCollisionCentreX() - getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                        getCollisionCentreX() - getCollisionBoxSideHalf() > float(tile_p->getX()))) {
                    if (getCollisionCentreY() - getCollisionBoxSideHalf() > float(tile_p->getCentreY())) {
                        yMomentum = 0.1f;
                    } else if (getCollisionCentreY() + getCollisionBoxSideHalf() < float(tile_p->getCentreY())) {
                        yMomentum = -0.1f;
                    }
                }
                break;
            case tile::bouncy:
                if ((getCollisionCentreY() + getCollisionBoxSideHalf() < float(tile_p->getY()) + TILE_HEIGHT &&
                     getCollisionCentreY() + getCollisionBoxSideHalf() > float(tile_p->getY()))
                    || (getCollisionCentreY() - getCollisionBoxSideHalf() < float(tile_p->getY()) + TILE_HEIGHT &&
                        getCollisionCentreY() - getCollisionBoxSideHalf() > float(tile_p->getY()))) {
                    if (getCollisionCentreX() - getCollisionBoxSideHalf() > float(tile_p->getCentreX())) {
                        xMomentum = std::abs(xMomentum) * 0.9f;
                    } else {
                        xMomentum = std::abs(xMomentum) * -0.9f;
                    }
                }

                if ((getCollisionCentreX() + getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                     getCollisionCentreX() + getCollisionBoxSideHalf() > float(tile_p->getX()))
                    || (getCollisionCentreX() - getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                        getCollisionCentreX() - getCollisionBoxSideHalf() > float(tile_p->getX()))) {
                    if (getCollisionCentreY() - getCollisionBoxSideHalf() > float(tile_p->getCentreY())) {
                        yMomentum = std::abs(yMomentum) * 0.9f;
                    } else {
                        yMomentum = std::abs(yMomentum) * -0.9f;
                    }
                }
                break;
            case tile::passable:
                break;
        }
    }

    if (std::abs(xMomentum) > 0.01f || std::abs(yMomentum) > 0.01f) {

        x += xMomentum;
        y += yMomentum;
        actor::sprite.setPosition(x, y);
    }

}

void actor::flipSprite(bool left, bool moveLeft) {
    if (spriteFlipped && !left && !moveLeft) {
        spriteFlipped = false;
    } else if (left) {
        spriteFlipped = true;
    }
}
