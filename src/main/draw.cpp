#include "draw.h"
#include "actor/actor.h"

void draw::render(world& gameWorld_p, sf::RenderWindow& mainWindow_p, std::vector<actor*>& actors_p, std::vector<textContainer*>& texts_p) {
    mainWindow_p.clear(sf::Color(200, 100, 200));

    std::vector<std::vector<tile>> tiles = gameWorld_p.getTiles();

    for (int i = 0; i < tiles.capacity() - 1; ++i) {
        std::vector<tile> row = tiles[i];
        for (int j = 0; j < row.capacity(); ++j) {
            mainWindow_p.draw(row[j].getSprite());
        }
    }

    for (int i = 0; i < actors_p.capacity(); ++i) {
        actors_p[i]->animate();
        mainWindow_p.draw(actors_p[i]->getSprite());
    }

    for (int i = 0; i < texts_p.capacity(); ++i) {
        mainWindow_p.draw(texts_p[i]->getText());
    }

    mainWindow_p.display();
}