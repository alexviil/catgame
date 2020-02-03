#include "game.h"

game::state game::gameState = uninitialized;
sf::RenderWindow game::mainWindow;

int game::start() {
    mainWindow.create(sf::VideoMode(1280, 720, 32), "Cat Game Project!");

    while(gameState != game::exiting) {
        mainLoop();
    }

    mainWindow.close();

    return 0;
}

void game::mainLoop() {
    sf::Event currentEvent{};
    while(mainWindow.pollEvent(currentEvent)) {

        mainWindow.clear(sf::Color(255, 100, 255));
        mainWindow.display();

        if (currentEvent.type == sf::Event::Closed) {
            gameState = game::exiting;
        }
    }
}