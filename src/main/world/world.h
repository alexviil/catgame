#ifndef CATGAME_WORLD_H
#define CATGAME_WORLD_H


#include <vector>
#include "tile.h"

class world {
private:
    std::vector<std::vector<tile>> tiles;
    sf::Texture default_tile_texture;

public:
    world();

    const std::vector<std::vector<tile>> &getTiles() const;
    void setTiles(const std::vector<std::vector<tile>> &newTiles);
};


#endif //CATGAME_WORLD_H
