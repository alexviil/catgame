#include <SFML/Graphics/View.hpp>
#include "player.h"

player::player(float x, float y, float speed, const sf::Texture& currentTexture) : actor(x, y, speed, currentTexture) {}

void player::move(sf::View& mainView, world& gameWorld, std::vector<actor*> &actors) {
    actor::move(inputMovingUp, inputMovingRight, inputMovingDown, inputMovingLeft, gameWorld, actors);
    mainView.setCenter(x, y);
}

void player::attack() {
    actor::attack();
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
