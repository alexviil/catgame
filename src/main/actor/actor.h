#pragma once
#ifndef CATGAME_ACTOR_H
#define CATGAME_ACTOR_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class actor {
public:
    actor(float x, float y, float speed, const sf::Texture& currentTexture);

    void animate();

    sf::Sprite &getSprite();
    float getX() const;
    float getY() const;
    float getCollisionX();
    float getCollisionY();
    float getCollisionRadius();

protected:
    enum animationStates {idle, walking, attacking};

    float x;
    float xMomentum = 0.f;
    float y;
    float yMomentum = 0.f;
    float maxMomentum;
    float acceleration = 20.f;
    float deceleration = 10.f;

    float collisionRadius = 20.f;

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
};


#endif //CATGAME_ACTOR_H
