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

    bool operator > (const actor &other) const;

    void animate();
    void move(bool, bool, bool, bool, world& gameWorld, std::vector<actor*>& actors);
    void lookAt(float, float);
    virtual void attack();

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

protected:
    enum states {idle, walking, attacking};
    enum directions {up, right, left, down};

    float x;
    float xMomentum = 0.f;
    float y;
    float yMomentum = 0.f;
    float maxMomentum;
    sf::Clock movementClock;

    float collisionBoxSideHalf = 14.f;

    actor::states state = idle;
    actor::directions direction = down;
    sf::Sprite sprite;
    sf::Clock animationClock;
    unsigned int animationFrames;
    unsigned int currentFrame = 0;

    // ATTRIBUTES
    // Main
    float hp = 100.f;
    float unarmedDamage = 5.f;
    // Speed & Traction
    float acceleration = 20.f;
    float deceleration = 10.f;
    // Attacking
    float attackSpeed = 10.f;
    float attackCooldown = 1.5f;
    sf::Clock attackClock;

private:
    sf::Texture currentTexture;

};


#endif //CATGAME_ACTOR_H
