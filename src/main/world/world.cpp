#include <iostream>
#include "world.h"
#include "tile.h"
#include "../../constants.h"

std::vector<std::vector<tile>> &world::getTiles(){
    return tiles;
}

world::world(textureManager &textureManager) {
    srand(time(nullptr));
    for (int i = 0; i <= 1200; i += TILE_WIDTH) {
        std::vector<tile> row;
        for (int j = 0; j <= 720; j += TILE_HEIGHT) {
            int frame = rand() % 5;
            if (frame == 4) {
                frame = rand() % 5;
            }
            row.emplace_back(i, j, textureManager.getTexture(SPRITE_TILE_DEFAULT), frame,
                    frame == 4 ? tile::tileState::blocked : tile::tileState::passable);
        }
        row.emplace_back(i, 768, textureManager.getTexture(SPRITE_TILE_BOUNCY), 0, tile::tileState::bouncy);
        tiles.push_back(row);
    }
}

std::vector<tile*> world::getTilesByCoordsSquare(float x, float y, float side) {
    std::vector<tile*> tilesInRange;
    for (int i = x - side; i <= x + side; i += side) {
        for (int j = y - side; j <= y + side; j += side) {
            tilesInRange.push_back(&tiles[i / TILE_WIDTH][j / TILE_HEIGHT]);
        }
    }

    sort(tilesInRange.begin(), tilesInRange.end());
    tilesInRange.erase(unique(tilesInRange.begin(), tilesInRange.end()), tilesInRange.end());
    tilesInRange.shrink_to_fit();

    return tilesInRange;
}

std::vector<tile*> world::getTilesByCoordsCircle(float x, float y, float radius) {
    std::vector<tile*> tilesInRange;
    for (int i = x - radius; i < x + radius; i += radius / 2.f) {
        for (int j = y - radius; j < y + radius; j += radius / 2.f) {
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius ) {
                tilesInRange.push_back(&tiles[i / TILE_WIDTH][j / TILE_HEIGHT]);
            }
        }
    }

    sort(tilesInRange.begin(), tilesInRange.end());
    tilesInRange.erase(unique(tilesInRange.begin(), tilesInRange.end()), tilesInRange.end());
    tilesInRange.shrink_to_fit();

    return tilesInRange;
}
