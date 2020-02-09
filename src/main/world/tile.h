#pragma once
#ifndef CATGAME_TILE_H
#define CATGAME_TILE_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class tile {
public:
    enum tileState {passable, blocked, bouncy};

    tile(int x, int y, const sf::Texture &texture, int frame, tile::tileState);

    const sf::Sprite &getSprite() const;
    tileState getState() const;
    int getDecelerationCoefficient() const;
    void setDecelerationCoefficient(int decelerationCoefficient);
    int getX() const;
    int getY() const;
    int getCentreX() const;
    int getCentreY() const;

private:
    tile::tileState state;
    int x;
    int y;
    int decelerationCoefficient = 0;
    sf::Sprite sprite;
};


#endif //CATGAME_TILE_H
