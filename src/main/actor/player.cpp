#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <cmath>
#include "player.h"
#include "../../constants.h"

player::player(float x, float y, float speed, const sf::Texture& currentTexture) : actor(x, y, speed, currentTexture) {}

void player::move(sf::View& mainView, world& gameWorld) {
    float time = inputClock.restart().asSeconds();

    if (inputMovingUp || inputMovingRight || inputMovingLeft || inputMovingDown) {
        player::animatonState = walking;
        if (inputMovingUp && yMomentum >= -maxMomentum) {
            yMomentum -= time * acceleration * (inputMovingLeft || inputMovingRight ? 0.86603f : 1.f);
        } else if (inputMovingDown && yMomentum <= maxMomentum) {
            yMomentum += time * acceleration * (inputMovingLeft || inputMovingRight ? 0.86603f : 1.f);
        } else {
            momentumDecay(time);
        }
        if (inputMovingLeft && xMomentum >= -maxMomentum) {
            flipSprite(true);
            xMomentum -= time * acceleration * (inputMovingUp || inputMovingDown ? 0.86603f : 1.f);
        } else if (inputMovingRight && xMomentum <= maxMomentum) {
            flipSprite(false);
            xMomentum += time * acceleration * (inputMovingUp || inputMovingDown ? 0.86603f : 1.f);
        } else {
            momentumDecay(time);
        }

        if (std::abs(xMomentum) > 0.86603f * maxMomentum && std::abs(yMomentum) > 0.86603f * maxMomentum) {
            xMomentum = 0.86603f * maxMomentum * (float(xMomentum > 0) - float(xMomentum < 0));
            yMomentum = 0.86603f * maxMomentum * (float(yMomentum > 0) - float(yMomentum < 0));
        }
    } else {
        player::animatonState = idle;
        momentumDecay(time);
    }

    std::vector<tile*> nextTiles = gameWorld.getTilesByCoordsSquare(getCollisionCentreX() + xMomentum, getCollisionCentreY() + yMomentum,
                                                                    getCollisionBoxSideHalf());
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
                        xMomentum = std::abs(xMomentum) * 1.25f;
                    } else {
                        xMomentum = std::abs(xMomentum) * -1.25f;
                    }
                }

                if ((getCollisionCentreX() + getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                     getCollisionCentreX() + getCollisionBoxSideHalf() > float(tile_p->getX()))
                    || (getCollisionCentreX() - getCollisionBoxSideHalf() < float(tile_p->getX()) + TILE_WIDTH &&
                        getCollisionCentreX() - getCollisionBoxSideHalf() > float(tile_p->getX()))) {
                    if (getCollisionCentreY() - getCollisionBoxSideHalf() > float(tile_p->getCentreY())) {
                        yMomentum = std::abs(yMomentum) * 1.25f;
                    } else {
                        yMomentum = std::abs(yMomentum) * -1.25f;
                    }
                }
                break;
            case tile::passable:
                break;
        }
    }

    std::cout << "-----\n";
    std::cout << getCollisionCentreX() << ";" << getCollisionCentreY() << std::endl;

    if (std::abs(xMomentum) > 0.01f || std::abs(yMomentum) > 0.01f) {

        x += xMomentum;
        y += yMomentum;
        player::sprite.setPosition(x, y);
        mainView.setCenter(getCollisionCentreX(), getCollisionCentreY());
    }

}

void player::momentumDecay(float time) {
    if (!inputMovingUp && !inputMovingDown) {
        yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
    }
    if (!inputMovingLeft && !inputMovingRight) {
        xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
    }
    /*
    if (std::abs(xMomentum) < 0.01f) {xMomentum = 0.f;}
    if (std::abs(yMomentum) < 0.01f) {yMomentum = 0.f;}
     */
}

void player::flipSprite(bool left) {
    if (spriteFlipped && !left && !inputMovingLeft) {
        spriteFlipped = false;
    } else if (left) {
        spriteFlipped = true;
    }
}

void player::setInputMovingUp(bool newInputMovingUp) {
    player::inputMovingUp = newInputMovingUp;
}

void player::setInputMovingDown(bool newInputMovingDown) {
    player::inputMovingDown = newInputMovingDown;
}

void player::setInputMovingLeft(bool newInputMovingLeft) {
    player::inputMovingLeft = newInputMovingLeft;
}

void player::setInputMovingRight(bool newInputMovingRight) {
    player::inputMovingRight = newInputMovingRight;
}