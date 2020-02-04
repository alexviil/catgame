#include <iostream>
#include "player.h"

player::player(float x, float y, float speed, sf::Texture *currentTexture) : actor(x, y, speed, currentTexture) {}

void player::move(float time) {
    if (movingUp) {
        y -= speed * time;
    } else if (movingDown) {
        y += speed * time;
    }
    if (movingLeft) {
        x -= speed * time;
    } else if (movingRight) {
        x += speed * time;
    }

    player::sprite.setPosition(x, y);
}

