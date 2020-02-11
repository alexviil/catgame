#include <iostream>
#include "draw.h"
#include "actor/actor.h"
#include "../constants.h"

void draw::render(sf::View& view, world& gameWorld_p, sf::RenderWindow& mainWindow_p, std::vector<actor*>& actors_p, std::vector<textContainer*>& texts_p) {
    mainWindow_p.clear(sf::Color(200, 100, 200));
    float x1 = view.getCenter().x - view.getSize().x / 2 - TILE_WIDTH;
    float y1 = view.getCenter().y - view.getSize().y / 2 - TILE_HEIGHT;
    float x2 = view.getCenter().x + view.getSize().x / 2;
    float y2 = view.getCenter().y + view.getSize().y / 2;

    std::vector<std::vector<tile>> tiles = gameWorld_p.getTiles();

    for (int i = 0; i < tiles.size() - 1; ++i) {
        std::vector<tile> row = tiles[i];
        for (auto & tile : row) {
            if (float(tile.getX()) > x1 && float(tile.getX()) < x2
            && float(tile.getY()) > y1 && float(tile.getY()) < y2) {
                mainWindow_p.draw(tile.getSprite());
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