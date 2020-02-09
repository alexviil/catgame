#pragma once
#ifndef CATGAME_WORLD_H
#define CATGAME_WORLD_H


#include <vector>
#include <set>
#include "tile.h"
#include "../textureManager.h"

class world {
public:
    explicit world(textureManager& textureManager);

    std::vector<std::vector<tile>> &getTiles();

    std::vector<tile*> getTilesByCoordsCircle(float, float, float);
    std::vector<tile*> getTilesByCoordsSquare(float, float, float);

private:
    std::vector<std::vector<tile>> tiles;
    tile nullTile = tile(0, 0, sf::Texture(), 0, tile::bouncy);
};


#endif //CATGAME_WORLD_H
