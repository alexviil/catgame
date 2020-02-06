#pragma once
#ifndef CATGAME_ACTOR_H
#define CATGAME_ACTOR_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class actor {
public:
    actor(float x, float y, float speed, const sf::Texture& currentTexture);

    sf::Sprite &getSprite();

    float getX() const;

    float getXMomentum() const;

    float getY() const;

    float getYMomentum() const;

protected:
    float x;
    float xMomentum = 0.f;
    float y;
    float yMomentum = 0.f;
    float maxMomentum;
    float acceleration = 20.f;
    float deceleration = 10.f;

    sf::Sprite sprite;
    sf::Clock animationClock;
    bool spriteFlipped = false;

private:
    /*
    int hp;
    int armor;
    int dmg;
    ...
    */

    sf::Texture currentTexture;

    /* TODO
    sf::Texture idleTextureSheet;
    sf::Texture moveTextureSheet;
    sf::Texture jumpTextureSheet;
    sf::Texture useItemTextureSheet;
    sf::Texture attackBasicTextureSheet;
    sf::Texture attackStrongTextureSheet;
    ...
    */
};


#endif //CATGAME_ACTOR_H
