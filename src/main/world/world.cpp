#include "world.h"
#include "../../constants.h"

const std::vector<std::vector<tile>> &world::getTiles() const {
    return tiles;
}

void world::setTiles(const std::vector<std::vector<tile>> &newTiles) {
    world::tiles = newTiles;
}

world::world() {
    default_tile_texture.loadFromFile(SPRITE_TILE_DEFAULT);
    for (int i = 128; i <= 1152; i += TILE_WIDTH) {
        std::vector<tile> row;
        for (int j = 128; j <= 592; j += TILE_HEIGHT) {
            row.emplace_back(i, j, &default_tile_texture);
        }
        tiles.push_back(row);
    }
}
