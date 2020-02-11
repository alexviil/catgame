#pragma once
#ifndef CATGAME_PLAYER_H
#define CATGAME_PLAYER_H


#include "actor.h"
#include "../world/world.h"
#include <SFML/Graphics/View.hpp>

class player: public actor {
public:
    player(float x, float y, float speed, const sf::Texture& currentTexture);

    void move(sf::View&, world&, std::vector<actor*>&);
    void momentumDecay(float);
    void flipSprite(bool);

    void setInputMovingUp(bool inputMovingUp);
    void setInputMovingDown(bool inputMovingDown);
    void setInputMovingLeft(bool inputMovingLeft);
    void setInputMovingRight(bool inputMovingRight);

private:
    sf::Clock inputClock;
    bool inputMovingUp = false;
    bool inputMovingDown = false;
    bool inputMovingLeft = false;
    bool inputMovingRight = false;
};


#endif //CATGAME_PLAYER_H
