#include <SFML/Graphics/View.hpp>
#include "player.h"
#include "../../constants.h"

player::player(float x, float y, float speed, const sf::Texture& currentTexture) : actor(x, y, speed, currentTexture) {}

void player::move(sf::View* mainView) {
    float time = inputClock.restart().asSeconds();

    if (inputMovingUp || inputMovingRight || inputMovingLeft || inputMovingDown) {

        if (inputMovingUp && yMomentum >= -maxMomentum) {
            yMomentum -= time * acceleration * (inputMovingLeft || inputMovingRight ? 0.86603f : 1.f);
        } else if (inputMovingDown && yMomentum <= maxMomentum) {
            yMomentum += time * acceleration * (inputMovingLeft || inputMovingRight ? 0.86603f : 1.f);
        } else {
            yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
        }
        if (inputMovingLeft && xMomentum >= -maxMomentum) {
            if (!spriteFlipped) {
                spriteFlipped = true;
                getSprite().setTextureRect(sf::IntRect(TILE_WIDTH, 0, -TILE_WIDTH, TILE_HEIGHT));
            }
            xMomentum -= time * acceleration * (inputMovingUp || inputMovingDown ? 0.86603f : 1.f);
        } else if (inputMovingRight && xMomentum <= maxMomentum) {
            if (spriteFlipped) {
                spriteFlipped = false;
                getSprite().setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_HEIGHT));
            }
            xMomentum += time * acceleration * (inputMovingUp || inputMovingDown ? 0.86603f : 1.f);
        } else {
            xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
        }

        if (std::abs(xMomentum) > 0.86603f * maxMomentum && std::abs(yMomentum) > 0.86603f * maxMomentum) {
            xMomentum = 0.86603f * maxMomentum * (float(xMomentum > 0) - float(xMomentum < 0));
            yMomentum = 0.86603f * maxMomentum * (float(yMomentum > 0) - float(yMomentum < 0));
        }

    } else {
        xMomentum -= std::abs(xMomentum) < 0.01f ? 0.f : xMomentum * time * deceleration;
        yMomentum -= std::abs(yMomentum) < 0.01f ? 0.f : yMomentum * time * deceleration;
    }

    if (std::abs(xMomentum) < 0.01f) {
        xMomentum = 0.f;
    }
    if (std::abs(yMomentum) < 0.01f) {
        yMomentum = 0.f;
    }

    if (std::abs(xMomentum) > 0.01f || std::abs(yMomentum) > 0.01f) {
        x += xMomentum;
        y += yMomentum;
        player::sprite.setPosition(x, y);
        mainView->setCenter(x + TILE_WIDTH / 2.f, y + TILE_HEIGHT / 2.f);
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
