#pragma once
#ifndef CATGAME_ACTOR_H
#define CATGAME_ACTOR_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include "../world/world.h"

class actor {
public:
    actor(float x, float y, float speed, const sf::Texture& currentTexture);

    bool operator> (const actor &other) const;

    void animate();
    void move(bool, bool, bool, bool, world& gameWorld, std::vector<actor*>& actors);

    sf::Sprite &getSprite();
    float getX() const;
    float getY() const;
    float getCollisionCentreX();
    float getCollisionCentreY();
    float getCollisionBoxSideHalf();
    float getCollisionX1();
    float getCollisionX2();
    float getCollisionY1();
    float getCollisionY2();
    float getXMomentum() const;
    float getYMomentum() const;

protected:
    enum animationStates {idle, walking, attacking};

    float x;
    float xMomentum = 0.f;
    float y;
    float yMomentum = 0.f;
    float maxMomentum;
    float acceleration = 20.f;
    float deceleration = 10.f;
    sf::Clock movementClock;

    float collisionBoxSideHalf = 14.f;

    actor::animationStates animatonState = idle;
    actor::animationStates previousAnimationState = idle;
    sf::Sprite sprite;
    sf::Clock animationClock;
    unsigned int animationFrames;
    unsigned int currentFrame = 0;
    bool spriteFlipped = false;

private:
    /*
    int hp;
    int armor;
    int dmg;
    ...
    */

    sf::Texture currentTexture;

    void momentumDecay(float, bool, bool, bool, bool);

    void flipSprite(bool, bool);
};


#endif //CATGAME_ACTOR_H
