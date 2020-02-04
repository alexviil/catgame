#ifndef CATGAME_PLAYER_H
#define CATGAME_PLAYER_H


#include "actor.h"

class player: public actor {
public:
    player(float x, float y, float speed, sf::Texture *currentTexture);

    void move(float time);

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;
};


#endif //CATGAME_PLAYER_H
