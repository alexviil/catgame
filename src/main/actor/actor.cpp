#include <cmath>
#include <iostream>
#include "actor.h"
#include "../../constants.h"

actor::actor(float x, float y, float speed, const sf::Texture& currentTexture) : x(x), y(y), maxMomentum(speed),
                                                                           currentTexture(currentTexture) {
    actor::sprite.setPosition(sf::Vector2f(x, y));
    actor::sprite.setTexture(currentTexture);
    actor::sprite.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    animationFrames = currentTexture.getSize().x / TILE_WIDTH;
}

void actor::animate() {
    //https://www.gamefromscratch.com/post/2015/10/26/SFML-CPP-Tutorial-Spritesheets-and-Animation.aspx
    float time = animationClock.getElapsedTime().asSeconds();

    switch (state) {
        case idle:
            if (time >= 0.25f) {
                currentFrame++;
                if (currentFrame == animationFrames) {
                    currentFrame = 0;
                }
                actor::sprite.setTextureRect(sf::IntRect(TILE_WIDTH * currentFrame, 0, TILE_WIDTH, TILE_HEIGHT));
                animationClock.restart();
            }
            break;
        case walking:
            if (time >= 0.5f / sqrt(sqrt(xMomentum * xMomentum + yMomentum * yMomentum))) {
                currentFrame++;
                if (currentFrame == animationFrames) {
                    currentFrame = 0;
                }
                actor::sprite.setTextureRect(sf::IntRect(TILE_WIDTH * currentFrame, TILE_HEIGHT * (direction + 1), TILE_WIDTH, TILE_HEIGHT));
                animationClock.restart();
            }
            break;
        case attacking:
            if (time >= 1.f / actor::attackSpeed) {
                actor::sprite.setTextureRect(sf::IntRect(TILE_WIDTH * currentFrame, TILE_HEIGHT * (direction + 5), TILE_WIDTH, TILE_HEIGHT));
                animationClock.restart();
                currentFrame++;
                if (currentFrame == animationFrames) {
                    actor::state = actor::states::idle;
                    currentFrame = 0;
                }
            }
            break;
    }
}

void actor::move(bool moveUp, bool moveRight, bool moveDown, bool moveLeft, world& gameWorld, std::vector<actor*>& actors) {
    float time = movementClock.restart().asSeconds();

    if (actor::state != actor::states::attacking && (moveUp || moveRight || moveLeft || moveDown)) {

        actor::direction = moveLeft ? actor::directions::left : moveRight ? actor::directions::right : moveUp ? actor::directions::up : actor::directions::down;
        actor::state = walking;
        if (moveUp && yMomentum >= -maxMomentum) {
            yMomentum -= time * acceleration * (moveLeft || moveRight ? 0.86603f : 1.f);
        } else if (moveDown && yMomentum <= maxMomentum) {
            yMomentum += time * acceleration * (moveLeft || moveRight ? 0.86603f : 1.f);
        }
        if (moveLeft && xMomentum >= -maxMomentum) {
            xMomentum -= time * acceleration * (moveUp || moveDown ? 0.86603f : 1.f);
        } else if (moveRight && xMomentum <= maxMomentum) {
            xMomentum += time * acceleration * (moveUp || moveDown ? 0.86603f : 1.f);
        }

        if (!moveUp && !moveDown) {
            yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
        }
        if (!moveLeft && !moveRight) {
            xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
        }

        if (std::abs(xMomentum) > 0.86603f * maxMomentum && std::abs(yMomentum) > 0.86603f * maxMomentum) {
            xMomentum = 0.86603f * maxMomentum * (float(xMomentum > 0) - float(xMomentum < 0));
            yMomentum = 0.86603f * maxMomentum * (float(yMomentum > 0) - float(yMomentum < 0));
        }
    } else {
        if (actor::state == actor::states::walking) {
            actor::state = idle;
        }
        yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
        xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
    }

    std::vector<tile*> nextTiles = gameWorld.getTilesByCoordsSquare(getCollisionCentreX() + xMomentum,
            getCollisionCentreY() + yMomentum, getCollisionBoxSideHalf());
    // NOTE for a better collision system, a method which takes the entire path into account instead of just the landing
    //      will provide a more accurate system, especially at high speeds. Currently, speeds that surpass a tile's
    //      within the span of a tick ignores the passed tile.
    // NOTE2 instead of setting momentum as some arbitrary low value, set it as the maximum/minimum value that avoids
    //       collision by calculating distance.
    for (int i = 0; i < nextTiles.capacity(); ++i) {
        tile* tile_p = nextTiles[i];
        switch (tile_p->getState()) {
            case tile::blocked:
                if ((getCollisionY2() < float(tile_p->getY()) + TILE_HEIGHT && getCollisionY2() > float(tile_p->getY()))
                    || (getCollisionY1() < float(tile_p->getY()) + TILE_HEIGHT && getCollisionY1() > float(tile_p->getY()))) {
                    if (getCollisionX1() > float(tile_p->getCentreX())) {
                        xMomentum = 0.1f;
                    } else if (getCollisionX2() < float(tile_p->getCentreX())) {
                        xMomentum = -0.1f;
                    }
                }

                if ((getCollisionX2() < float(tile_p->getX()) + TILE_WIDTH && getCollisionX2() > float(tile_p->getX()))
                    || (getCollisionX1() < float(tile_p->getX()) + TILE_WIDTH && getCollisionX1() > float(tile_p->getX()))) {
                    if (getCollisionY1() > float(tile_p->getCentreY())) {
                        yMomentum = 0.1f;
                    } else if (getCollisionY2() < float(tile_p->getCentreY())) {
                        yMomentum = -0.1f;
                    }
                }
                break;
            case tile::bouncy:
                if ((getCollisionY2() < float(tile_p->getY()) + TILE_HEIGHT && getCollisionY2() > float(tile_p->getY()))
                    || (getCollisionY1() < float(tile_p->getY()) + TILE_HEIGHT && getCollisionY1() > float(tile_p->getY()))) {
                    if (getCollisionX1() > float(tile_p->getCentreX())) {
                        xMomentum = std::abs(xMomentum) * 0.9f;
                    } else {
                        xMomentum = std::abs(xMomentum) * -0.9f;
                    }
                }

                if ((getCollisionX2() < float(tile_p->getX()) + TILE_WIDTH && getCollisionX2() > float(tile_p->getX()))
                    || (getCollisionX1() < float(tile_p->getX()) + TILE_WIDTH && getCollisionX1() > float(tile_p->getX()))) {
                    if (getCollisionY1() > float(tile_p->getCentreY())) {
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

    for (auto & actor : actors) {
        if (actor != this
        && getCollisionX1() + xMomentum < actor->getCollisionX2()
        && getCollisionX2() + xMomentum > actor->getCollisionX1()
        && getCollisionY1() + yMomentum < actor->getCollisionY2()
        && getCollisionY2() + yMomentum > actor->getCollisionY1()) {
            if ((getCollisionY2() < actor->getCollisionY2() && getCollisionY2() > actor->getCollisionY1())
                || (getCollisionY1() < actor->getCollisionY2() && getCollisionY1() > actor->getCollisionY1())) {
                if (getCollisionX1() > actor->getCollisionX1()) {
                    xMomentum = 0.1f;
                } else if (getCollisionX2() < actor->getCollisionX1()) {
                    xMomentum = -0.1f;
                }
            }
            if ((getCollisionX2() < actor->getCollisionX2() && getCollisionX2() > actor->getCollisionX1())
                || (getCollisionX1() < actor->getCollisionX2() && getCollisionX1() > actor->getCollisionX1())) {
                if (getCollisionY1() > actor->getCollisionY1()) {
                    yMomentum = 0.1f;
                } else if (getCollisionY2() < actor->getCollisionY1()) {
                    yMomentum = -0.1f;
                }
            }
        }
    }

    if (std::abs(xMomentum) > 0.01f || std::abs(yMomentum) > 0.01f) {
        x += xMomentum;
        y += yMomentum;
        actor::sprite.setPosition(x, y);
    }

}

void actor::lookAt(float x, float y) {
    float radians = 2.35619f + atan2(actor::getCollisionCentreY() - y, actor::getCollisionCentreX() - x);
    if (radians <= 0 || radians > 4.71239) {
        actor::direction = actor::directions::right;
    } else if (radians <= 1.5708) {
        actor::direction = actor::directions::down;
    } else if (radians <= 3.14159) {
        actor::direction = actor::directions::left;
    } else {
        actor::direction = actor::directions::up;
    }
}


void actor::attack() {
    if (attackClock.getElapsedTime().asSeconds() > attackCooldown) {
        actor::currentFrame = 0;
        actor::state = actor::states::attacking;
        attackClock.restart();
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

float actor::getCollisionX1() {
    return getCollisionCentreX() - getCollisionBoxSideHalf();
}

float actor::getCollisionX2() {
    return getCollisionCentreX() + getCollisionBoxSideHalf();
}

float actor::getCollisionY1() {
    return getCollisionCentreY() - getCollisionBoxSideHalf();
}
float actor::getCollisionY2() {
    return getCollisionCentreY() + getCollisionBoxSideHalf();
}

bool actor::operator>(const actor &other) const {
    return y < other.getY();
}

bool actor::isHostile() const {
    return hostile;
}
