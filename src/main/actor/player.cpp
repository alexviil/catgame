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

    std::vector<tile*> nextTiles = gameWorld.getTilesByCoordsCircle(getCollisionX() + xMomentum, getCollisionY() + yMomentum, getCollisionRadius());
    for (int i = 0; i < nextTiles.capacity(); ++i) {
        tile* tile = nextTiles[i];
        switch (tile->getState()) {
            case tile::passable:
                break;
            case tile::blocked:
                if (getCollisionX() + 1 >= tile->getX() && getCollisionX() - 1 <= tile->getX() + TILE_WIDTH) {
                    yMomentum = (float(yMomentum < 0) - float(yMomentum > 0)) * 0.1f;
                }
                if (getCollisionY() + 1 >= tile->getY() && getCollisionY() - 1 <= tile->getY() + TILE_HEIGHT) {
                    xMomentum = (float(xMomentum < 0) - float(xMomentum > 0)) * 0.1f;
                }
                break;
            case tile::bouncy:
                if (getCollisionX() + 1 >= tile->getX() && getCollisionX() - 1 <= tile->getX() + TILE_WIDTH) {
                    yMomentum = -yMomentum * 1.5f;
                }
                if (getCollisionY() + 1 >= tile->getY() && getCollisionY() - 1 <= tile->getY() + TILE_HEIGHT) {
                    xMomentum = -xMomentum * 1.5f;
                }
                break;
        }
    }

    if (std::abs(xMomentum) > 0.01f || std::abs(yMomentum) > 0.01f) {
        x += xMomentum;
        y += yMomentum;
        player::sprite.setPosition(x, y);
        mainView.setCenter(x + TILE_WIDTH / 2.f, y + TILE_HEIGHT / 2.f);
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
        //getSprite().setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
    } else if (left) {
        spriteFlipped = true;
        //getSprite().setTextureRect(sf::IntRect(TILE_WIDTH, 0, -TILE_WIDTH, TILE_HEIGHT));
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