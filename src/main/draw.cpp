#include "draw.h"
#include "actor/actor.h"
#include "../constants.h"

void draw::render(sf::View& view, world& gameWorld_p, sf::RenderWindow& mainWindow_p, std::vector<actor*>& actors_p, std::vector<textContainer*>& texts_p) {
    mainWindow_p.clear(sf::Color(200, 100, 200));

    std::vector<std::vector<tile>> tiles = gameWorld_p.getTiles();

    for (int i = (view.getCenter().x - view.getSize().x / 2) / TILE_WIDTH; i < (view.getCenter().x + view.getSize().x / 2) / TILE_WIDTH; ++i) {
        for (int j = (view.getCenter().y - view.getSize().y / 2) / TILE_HEIGHT; j < (view.getCenter().y + view.getSize().y / 2) / TILE_HEIGHT; ++j) {
            if (i >= 0 && j >= 0 && i < tiles.size() && j < tiles[0].size()) { // stops crash when screen edges escape border
                mainWindow_p.draw(tiles[i][j].getSprite());
            }
        }
    }

    for (auto & actor : actors_p) {
        actor->animate();
        mainWindow_p.draw(actor->getSprite());
    }

    for (auto & text : texts_p) {
        mainWindow_p.draw(text->getText());
    }

    mainWindow_p.display();
}