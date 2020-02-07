#include <iostream>
#include "world.h"
#include "tile.h"
#include "../../constants.h"

std::vector<std::vector<tile>> &world::getTiles(){
    return tiles;
}

world::world(textureManager &textureManager) {
    srand(time(nullptr));
    for (int i = 0; i <= 2400; i += TILE_WIDTH) {
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

std::vector<tile*> world::getTilesByCoordsCircle(float x, float y, float radius) {
    std::vector<tile*> tilesInRange;
    for (int i = x - radius; i < x + radius; i += TILE_WIDTH / 4.f) {
        for (int j = y - radius; j < y + radius; j += TILE_HEIGHT / 4.f) {
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

bool world::Pred(tile& a, tile& b) {
    return a.getX() == b.getX() && a.getY() == b.getY();
}

